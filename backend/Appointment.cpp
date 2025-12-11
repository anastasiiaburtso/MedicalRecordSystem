#include "Appointment.h"

Appointment::Appointment(Doctor d, Patient p, std::string visitDate) 
    : doctor(d), patient(p), date(visitDate) {
}

std::string Appointment::getDetails() {
    return date + "|" + doctor.getName() + "|Запис|Прийом у лікаря";
}

std::string Appointment::getDate() {
    return date;
}