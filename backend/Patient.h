#ifndef PATIENT_H
#define PATIENT_H

#include <string>

class Patient {
private:
    int id;
    std::string name;
    std::string address; // Додавання адреси, щоб відрізнялося

public:
    Patient(int id, std::string name, std::string address);
    std::string getInfo();
};

#endif