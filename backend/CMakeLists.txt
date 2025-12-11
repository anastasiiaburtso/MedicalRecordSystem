cmake_minimum_required(VERSION 3.10)

# Назва проєкту
project(MedicalBackend)

# Вказування стандарту C++
set(CMAKE_CXX_STANDARD 14)

# Додавання X.cpp сюди через пробіл після main.cpp
add_executable(run_backend main.cpp Doctor.cpp Patient.cpp Appointment.cpp Prescription.cpp Referral.cpp)