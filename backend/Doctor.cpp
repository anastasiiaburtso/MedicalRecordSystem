#include "Doctor.h"

// Реалізація конструктора
// Дані, які  дали, і запис їх у "пам'ять" об'єкта
Doctor::Doctor(int inputId, std::string inputName, std::string inputSpecialization) {
    id = inputId;
    name = inputName;
    specialization = inputSpecialization;
}

// Реалізація методу getInfo
std::string Doctor::getInfo() {
    return "Лікар [ID: " + std::to_string(id) + "]: " + name + " (" + specialization + ")";
}