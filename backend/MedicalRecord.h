#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H
#include <string>

class MedicalRecord {
public:
    virtual std::string getDetails() = 0; 
    
    // Додаємо віртуальний метод для отримання дати (для сортування)
    virtual std::string getDate() = 0;

    virtual ~MedicalRecord() {}
};
#endif