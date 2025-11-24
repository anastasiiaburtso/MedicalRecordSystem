from flask import Flask, render_template

# Створення веб-застосунока
app = Flask(__name__)

# Головна сторінка (коли заходиш на сайт)
@app.route('/')
def home():
    return render_template('index.html')

if __name__ == '__main__':
    # Запускання серверу
    print("Запускання веб-сайта...")
    app.run(debug=True)