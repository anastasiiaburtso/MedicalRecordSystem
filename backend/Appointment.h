#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include "MedicalRecord.h"
#include "Doctor.h"
#include "Patient.h"

class Appointment : public MedicalRecord {
    private:
    std::string date;
    Doctor doctor;
    Patient patient;

    public:
    Appointment(Doctor d, Patient p, std::string visitDate);

    std::string getDetails() override;
    std::string getDate() override;
};

#endif