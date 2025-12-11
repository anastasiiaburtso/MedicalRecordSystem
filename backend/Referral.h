#ifndef REFERRAL_H
#define REFERRAL_H

#include "MedicalRecord.h"
#include "Doctor.h"
#include "Patient.h"
#include <string>

class Referral : public MedicalRecord {
private:
    Doctor doctor;
    Patient patient;
    std::string targetSpecialty; 
    std::string date;
public:
    Referral(Doctor d, Patient p, std::string spec, std::string dateStr);
    std::string getDetails() override;
    std::string getDate() override;
};
#endif