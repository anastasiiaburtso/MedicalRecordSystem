#include "Appointment.h"

// Реалізація конструктора (":" - це як Список ініціалізації)
// Використоання : doctor(d), patient(p), щоб "записати" людей у візит
Appointment::Appointment(Doctor d, Patient p, std::string visitDate) 
    : doctor(d), patient(p), date(visitDate) {
}

// Реалізація методу
std::string Appointment::getDetails() {
    return "Запис на прийом:\n" + 
           doctor.getInfo() + "\n" + 
           patient.getInfo() + "\n" +
           "Дата: " + date + "\n" + 
           "-------------------------";
}

std::string Appointment::getDate() {
    return date;
}