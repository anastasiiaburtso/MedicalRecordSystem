#include "Prescription.h"

Prescription::Prescription(Doctor d, Patient p, std::string med, std::string dose)
    : doctor(d), patient(p), medication(med), dosage(dose) {
}

std::string Prescription::getPrescriptionDetails() {
    return "    МЕДИЧНИЙ РЕЦЕПТ    \n" +
           doctor.getInfo() + "\n" +
           patient.getInfo() + "\n" +
           "Ліки: " + medication + "\n" +
           "Дозування: " + dosage + "\n" +
           "--------------------------------";
}