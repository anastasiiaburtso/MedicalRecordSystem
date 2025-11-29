#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include <string>
#include "Doctor.h"
#include "Patient.h"

class Prescription {
private:
    Doctor doctor;    // Хто виписав
    Patient patient;  // Кому виписали
    std::string medication; // Назва ліків 
    std::string dosage;     // Дозування 
public:
    // Конструктор
    Prescription(Doctor d, Patient p, std::string med, std::string dose);

    // Метод для друку рецепта
    std::string getPrescriptionDetails();
};

#endif