#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include <string>
#include "MedicalRecord.h"
#include "Doctor.h"
#include "Patient.h"

class Prescription : public MedicalRecord {
    private:
    Doctor doctor;    
    Patient patient;  
    std::string medication; 
    std::string dosage;     
    std::string date;
    
    public:
    Prescription(Doctor d, Patient p, std::string med, std::string dose, std::string dateString);

    std::string getDetails() override;
    std::string getDate() override;
};

#endif