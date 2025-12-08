import subprocess
import os
from flask import Flask, render_template, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'med_system_secret' # Ключ для захисту сесій

BACKEND_PATH = "./backend/run_backend"

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        role = request.form.get('role')
        name = request.form.get('name')
        # Зберігаємо роль та ім'я користувача
        session['role'] = role
        session['user_name'] = name if name else "Лікар"
        return redirect(url_for('dashboard'))
    return render_template('login.html')

@app.route('/dashboard')
def dashboard():
    if 'role' not in session:
        return redirect(url_for('login'))

    role = session['role']
    user_name = session['user_name']
    
    # Перевірка: чи натиснули кнопку "Сортувати"?
    sort_mode = request.args.get('sort') 
    
    output_text = ""
    if os.path.exists(BACKEND_PATH):
        try:
            # Формуємо команду для C++
            # history [Ім'я або ""] [sort або ""]
            cmd = [BACKEND_PATH, "history"]
            
            # Фільтр імені
            if role == 'patient':
                cmd.append(user_name)
            else:
                cmd.append("all") # Лікар бачить всіх ("all" - це просто заглушка, щоб аргументи не зсувалися)

            # Сортування
            if sort_mode == 'yes':
                cmd.append("sort")

            result = subprocess.run(cmd, capture_output=True, text=True)
            output_text = result.stdout
        except Exception as e:
            output_text = f"Помилка: {e}"

    return render_template('dashboard.html', role=role, name=user_name, cpp_output=output_text)

@app.route('/add', methods=['POST'])
def add_record():
    if session.get('role') == 'doctor':
        # Логіка додавання (як була раніше)
        subprocess.run([BACKEND_PATH, "add", session['user_name'], request.form.get('patient'), request.form.get('date')])
    return redirect(url_for('dashboard'))

@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True, port=5001)