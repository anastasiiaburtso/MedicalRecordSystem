#include <iostream>
#include "Doctor.h" 
#include "Patient.h"
#include "Appointment.h"

int main() {
    std::cout << "    Система запускається    " << std::endl;

    // Створення об'єкта лікаря (викликання конструктора)
    // ID: 1, Ім'я: Ян Хілл, Спеціалізація: Діагност
    Doctor doc1(1, "Ян Хілл", "Діагност");
    
    // Викликання методу getInfo(), щоб отримати рядок з даними, і виводення його
    std::cout << doc1.getInfo() << std::endl;

    // Створення другого лікаря
    Doctor doc2(2, "Джон Ватсон", "Хірург");
    std::cout << doc2.getInfo() << std::endl;

    Patient pat1(100, "Марк Грейсон", "Бейкер-стріт 221б" );
    std::cout << pat1.getInfo() << std::endl;

    std::cout << "\n Створення запису... " << std::endl;

    Appointment app1(doc1, pat1, "2023-11-01");
    std::cout << app1.getDetails() << std::endl;

    return 0;
}