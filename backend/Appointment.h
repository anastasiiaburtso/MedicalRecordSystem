#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include "Doctor.h"
#include "Patient.h"

class Appointment {
    private:
    std::string date;
    Doctor doctor;
    Patient patient;

    public:
    // Конструктор
    Appointment(Doctor d, Patient p, std::string visitDate);

    // Метод, щоб отримати деталі візиту
    std::string getDetails();
};

#endif