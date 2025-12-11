#include "Appointment.h"

// Реалізація конструктора (":" - це як Список ініціалізації)
// Використоання : doctor(d), patient(p), щоб "записати" людей у візит
Appointment::Appointment(Doctor d, Patient p, std::string visitDate) 
    : doctor(d), patient(p), date(visitDate) {
}

std::string Appointment::getDetails() {
    return date + "|" + doctor.getName() + "|Запис|Прийом у лікаря";
}

std::string Appointment::getDate() {
    return date;
}