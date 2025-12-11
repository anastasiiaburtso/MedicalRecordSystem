#include "Prescription.h"

Prescription::Prescription(Doctor d, Patient p, std::string med, std::string dose, std::string dateString)
    : doctor(d), patient(p), medication(med), dosage(dose),date(dateString) {
}

std::string Prescription::getDetails() {
    return date + "|" + doctor.getName() + "|Рецепт|" + medication + " " + dosage;
}
std::string Prescription::getDate() {
    return date;
}