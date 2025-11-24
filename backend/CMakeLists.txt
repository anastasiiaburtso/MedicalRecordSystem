cmake_minimum_required(VERSION 3.10)

# Назва проєкту
project(MedicalBackend)

# Вказання стандарту C++ (сучасний)
set(CMAKE_CXX_STANDARD 14)

# Створити програму з назвою "run_backend" із файлу "main.cpp"
add_executable(run_backend main.cpp)