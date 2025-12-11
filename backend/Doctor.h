#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <iostream>

class Doctor {
private:
    int id;
    std::string name;           
    std::string specialization; 


public:
    Doctor(int id, std::string name, std::string specialization);

    std::string getInfo(); 
    std::string getName();
};

#endif