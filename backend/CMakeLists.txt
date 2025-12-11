cmake_minimum_required(VERSION 3.10)

project(MedicalBackend)

set(CMAKE_CXX_STANDARD 14)

add_executable(run_backend main.cpp Doctor.cpp Patient.cpp Appointment.cpp Prescription.cpp Referral.cpp)