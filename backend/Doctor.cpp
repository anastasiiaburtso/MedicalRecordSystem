#include "Doctor.h"

Doctor::Doctor(int inputId, std::string inputName, std::string inputSpecialization) {
    id = inputId;
    name = inputName;
    specialization = inputSpecialization;
}

std::string Doctor::getInfo() {
    return "Лікар [ID: " + std::to_string(id) + "]: " + name + " (" + specialization + ")";
}

std::string Doctor::getName() {
    return name;
}