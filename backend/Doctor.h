#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <iostream>

class Doctor {
private:
    // Поля класу (характеристики лікаря)
    int id;
    std::string name;           // Ім'я
    std::string specialization; // Спеціалізація

public:
    // Конструктор (функція, яка створює лікаря)
    Doctor(int id, std::string name, std::string specialization);

    // Метод (що лікар вміє робити)
    std::string getInfo(); // Повертає текст з інформацією про лікаря
};

#endif