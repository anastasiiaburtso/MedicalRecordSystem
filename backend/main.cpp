#include <iostream>
#include "Doctor.h" 

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

    return 0;
}