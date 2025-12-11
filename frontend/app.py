import subprocess
import os
import json
from datetime import datetime, timedelta, date
from flask import Flask, render_template, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'med_key_secret'

BACKEND_PATH = "./backend/run_backend"
DOCTORS_FILE = "frontend/doctors.json"
PATIENTS_FILE = "frontend/patients.json"
APPOINTMENTS_FILE = "frontend/appointments.json"

# РОБОТА З ФАЙЛАМИ 
def load_json(file_path):
    if not os.path.exists(file_path): return []
    with open(file_path, 'r', encoding='utf-8') as f:
        return json.load(f)

def save_json(file_path, data):
    with open(file_path, 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=4, ensure_ascii=False)

def user_exists(file_path, name, key='name'):
    users = load_json(file_path)
    for u in users:
        if u.get(key) == name: return True
    return False

def check_credentials(file_path, name, password):
    users = load_json(file_path)
    for u in users:
        if u.get('name') == name and u.get('password') == password: return True
    return False

def get_slots(shift):
    slots = []
    start = datetime.strptime("08:00", "%H:%M") if int(shift) == 1 else datetime.strptime("14:00", "%H:%M")
    end = datetime.strptime("14:00", "%H:%M") if int(shift) == 1 else datetime.strptime("20:00", "%H:%M")
    while start < end:
        slots.append(start.strftime("%H:%M"))
        start += timedelta(minutes=30)
    return slots

def is_slot_taken(doc, d, t):
    for a in load_json(APPOINTMENTS_FILE):
        if a['doctor_name'] == doc and a['date'] == d and a['time'] == t: return True
    return False

# ВХІД / РЕЄСТРАЦІЯ 
@app.route('/', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        action = request.form.get('action')
        role = request.form.get('role')
        name = request.form.get('name')
        password = request.form.get('password')
        
        # АДМІН
        if action == 'register' and name == "Адмін" and password == "0951":
             if request.form.get('confirm_password') == "563645":
                 session['role'] = 'admin'
                 return redirect(url_for('admin_dashboard'))

        if role == 'doctor':
            if action == 'login':
                if check_credentials(DOCTORS_FILE, name, password):
                    session['role'], session['user_name'] = 'doctor', name
                    return redirect(url_for('dashboard'))
                else: error = "Невірні дані!"
            elif action == 'register':
                if user_exists(DOCTORS_FILE, name): error = "Вже існує!"
                else:
                    docs = load_json(DOCTORS_FILE)
                    docs.append({
                        "id": len(docs)+1, "name": name, "password": password,
                        "spec": request.form.get('spec'), "shift": int(request.form.get('shift'))
                    })
                    save_json(DOCTORS_FILE, docs)
                    session['role'], session['user_name'] = 'doctor', name
                    return redirect(url_for('dashboard'))

        elif role == 'patient':
            if action == 'login':
                if check_credentials(PATIENTS_FILE, name, password):
                    session['role'], session['user_name'] = 'patient', name
                    return redirect(url_for('dashboard'))
                else: error = "Невірні дані!"
            elif action == 'register':
                if user_exists(PATIENTS_FILE, name): error = "Вже існує!"
                else:
                    pats = load_json(PATIENTS_FILE)
                    pats.append({"name": name, "password": password})
                    save_json(PATIENTS_FILE, pats)
                    session['role'], session['user_name'] = 'patient', name
                    return redirect(url_for('dashboard'))
    return render_template('login.html', error=error)

@app.route('/admin')
def admin_dashboard():
    if session.get('role') != 'admin': return redirect(url_for('login'))
    users = []
    for d in load_json(DOCTORS_FILE): d['role']='doctor'; users.append(d)
    for p in load_json(PATIENTS_FILE): p['role']='patient'; users.append(p)
    return render_template('admin.html', users=users)

# КАБІНЕТ
@app.route('/dashboard')
def dashboard():
    if 'role' not in session: return redirect(url_for('login'))
    role, user_name = session['role'], session['user_name']
    
    # 1. Дати
    today_str = date.today().strftime("%Y-%m-%d")
    selected_date_str = request.args.get('date', today_str)
    if selected_date_str < today_str: selected_date_str = today_str
    is_weekend = datetime.strptime(selected_date_str, "%Y-%m-%d").weekday() >= 5

   
    patient_search = request.args.get('patient_search', '').strip()
    patient_found = False
    error_msg = None

    if role == 'doctor' and patient_search:
        if user_exists(PATIENTS_FILE, patient_search):
            patient_found = True
        else:
            error_msg = "Пацієнта не знайдено! Перевірте ім'я."
            patient_search = "" 

    # 3. Історія 
    medical_records = []
    should_load = (role == 'patient') or (role == 'doctor' and patient_found)

    if should_load and os.path.exists(BACKEND_PATH):
        try:
            cmd = [BACKEND_PATH, "history"]
            target = user_name if role == 'patient' else patient_search
            cmd.append(target)
            
            cmd.append("sort")
            if request.args.get('sort') == 'desc': cmd.append("sort_desc")
            else: cmd.append("sort_asc")

            res = subprocess.run(cmd, capture_output=True, text=True)
            for line in res.stdout.strip().split('\n'):
                parts = line.split('|')
                if len(parts) >= 4:
                    medical_records.append({'date': parts[0], 'doctor': parts[1], 'type': parts[2], 'details': parts[3]})
        except: pass

    
    all_doctors = load_json(DOCTORS_FILE)
    doctor_card = None
    
    
    current_doc_obj = None
    if role == 'doctor':
        for d in all_doctors:
            if d['name'] == user_name:
                current_doc_obj = d
                if is_weekend: current_doc_obj['available_slots'] = []
                else:
                    slots = get_slots(d['shift'])
                    current_doc_obj['available_slots'] = [s for s in slots if not is_slot_taken(user_name, selected_date_str, s)]
                break

    # Для пацієнта: вибір лікаря
    selected_doctor_name = request.args.get('doctor_select')
    if role == 'patient' and selected_doctor_name:
        for doc in all_doctors:
            if doc['name'] == selected_doctor_name:
                if is_weekend: doc['available_slots'] = []
                else:
                    slots = get_slots(doc['shift'])
                    doc['available_slots'] = [s for s in slots if not is_slot_taken(doc['name'], selected_date_str, s)]
                doctor_card = doc
                break

    return render_template('dashboard.html', role=role, name=user_name, 
                           records=medical_records, all_doctors=all_doctors, 
                           doctor_card=doctor_card, 
                           current_doc=current_doc_obj, # Передаємо лікаря
                           selected_date=selected_date_str, today=today_str, 
                           is_weekend=is_weekend, error=error_msg,
                           patient_search=patient_search) # Повертаємо пошук

# ДОДАВАННЯ 
@app.route('/add', methods=['POST'])
def add_record():
    if 'role' not in session: return redirect(url_for('login'))
    type_rec = request.form.get('type')
    
    # 1. ЗАПИС НА ПРИЙОМ 
    if type_rec == 'appointment':
        doc = request.form.get('doctor')
        pat = request.form.get('patient') 
        if not pat: pat = session['user_name']
        
        d, t = request.form.get('date'), request.form.get('time')
        
        if is_slot_taken(doc, d, t): return "Зайнято!", 400

        appts = load_json(APPOINTMENTS_FILE)
        appts.append({"doctor_name": doc, "patient_name": pat, "date": d, "time": t})
        save_json(APPOINTMENTS_FILE, appts)
        
        subprocess.run([BACKEND_PATH, "add", doc, pat, f"{d} {t}"])
        
        
        if session['role'] == 'doctor':
            return redirect(url_for('dashboard', patient_search=pat))

    # 2. РЕЦЕПТ 
    elif type_rec == 'prescription':
        pat = request.form.get('patient')
        date_val = datetime.now().strftime("%Y-%m-%d")
        full_med = request.form.get('med') 
        subprocess.run([BACKEND_PATH, "add", "P", session['user_name'], pat, full_med, " ", date_val])
        
        return redirect(url_for('dashboard', patient_search=pat)) 

    # 3. НАПРАВЛЕННЯ
    elif type_rec == 'referral':
        pat = request.form.get('patient')
        date_val = datetime.now().strftime("%Y-%m-%d")
        subprocess.run([BACKEND_PATH, "add", "R", session['user_name'], pat, request.form.get('target_spec'), date_val])
        
        return redirect(url_for('dashboard', patient_search=pat)) 

    return redirect(url_for('dashboard'))

@app.route('/logout')
def logout(): session.clear(); return redirect(url_for('login'))

if __name__ == '__main__': app.run(debug=True, port=5001)