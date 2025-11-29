#include "Patient.h"

Patient::Patient(int inputId, std::string inputName, std::string inputAddress) {
    id = inputId;
    name = inputName;
    address = inputAddress;
}

std::string Patient::getInfo() {
    return "Пацієнт [ID: " + std::to_string(id) + "]: " + name + " (Адреса: " + address + ")";
}