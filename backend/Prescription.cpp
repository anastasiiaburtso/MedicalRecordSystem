#include "Prescription.h"

Prescription::Prescription(Doctor d, Patient p, std::string med, std::string dose, std::string dateString)
    : doctor(d), patient(p), medication(med), dosage(dose),date(dateString) {
}

std::string Prescription::getDetails() {
    return "РЕЦЕПТ (" + date + "):\n" + 
           doctor.getInfo() + "\n" + 
           patient.getInfo() + "\n" +
           "Ліки: " + medication + " " + dosage + "\n";
}

std::string Prescription::getDate() {
    return date;
}