import subprocess
import os
from flask import Flask, render_template

# Створення веб-застосунока
app = Flask(__name__)

# Головна сторінка (коли заходиш на сайт)
@app.route('/')
def home():
    # Шлях до C++ програми
    # Припускання, що запуск python з головної папки проєкту
    backend_path = "./backend/run_backend"
    
    output_text = ""

    # Перевірка, чи існує файл про всяк випадок
    if os.path.exists(backend_path):
        try:
            # ЗАПУСК C++: Python запускає твою програму і "ловить" те, що вона пише
            result = subprocess.run(
                [backend_path], 
                capture_output=True, 
                text=True, 
                check=True
            )
            # Зберігання результату роботи C++ у змінну
            output_text = result.stdout
        except subprocess.CalledProcessError as e:
            output_text = f"Помилка при запуску C++: {e}"
    else:
        output_text = "Увага: Не знайдено файл backend/run_backend. Скомпілюйте C++ код!"

    # Віддавання тексту на сторінку index.html
    return render_template('index.html', cpp_output=output_text)

if __name__ == '__main__':
    app.run(debug=True)