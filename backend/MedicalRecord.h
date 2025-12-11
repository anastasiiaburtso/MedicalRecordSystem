#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H
#include <string>

class MedicalRecord {
public:
    virtual std::string getDetails() = 0; 
    
    virtual std::string getDate() = 0;

    virtual ~MedicalRecord() {}
};
#endif