#include <iostream>
#include "Doctor.h" 
#include "Patient.h"
#include "Appointment.h"
#include "Prescription.h"

int main() {
    std::cout << "    Система запускається    " << std::endl;

    // Створення об'єкта лікаря (викликання конструктора)
    Doctor doc1(1, "Ян Хілл", "Діагност");
    
    // Викликання методу getInfo(), щоб отримати рядок з даними, і виводення його
    std::cout << doc1.getInfo() << std::endl;

    Doctor doc2(2, "Джон Ватсон", "Хірург");
    std::cout << doc2.getInfo() << std::endl;

    Patient pat1(100, "Марк Грейсон", "Бейкер-стріт 221б" );
    std::cout << pat1.getInfo() << std::endl;

    std::cout << "\n Створення запису... " << std::endl;

    Appointment app1(doc1, pat1, "2023-11-01");
    std::cout << app1.getDetails() << std::endl;

    
    std::cout << "\nЛікар виписує рецепт... " << std::endl;
    
    Prescription rx1(doc1, pat1, "Нурофен", "1 таблетка при болю");
    std::cout << rx1.getPrescriptionDetails() << std::endl;

    return 0;
}