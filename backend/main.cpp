#include <iostream>
#include <vector>
#include <string> 
#include <fstream>
#include <sstream>
#include <algorithm> 
#include "MedicalRecord.h"
#include "Appointment.h"
#include "Prescription.h"
#include "Doctor.h"
#include "Patient.h"

// Допоміжна функція для розбиття рядка
std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main(int argc, char* argv[]) {
    // 1. Базова перевірка
    if (argc < 2) {
        std::cout << "Error: No command provided" << std::endl;
        return 1; 
    }

    std::string command = argv[1];

    if (command == "test") {
        std::cout << "Backend is online." << std::endl;
    }
    else if (command == "history") {
        std::vector<MedicalRecord*> history;
        std::string filterName = "";
        bool sortNeeded = false;

        // 2. Розумна перевірка аргументів (шукаємо ім'я та слово "sort")
        for (int i = 2; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "sort") {
                sortNeeded = true;
            } else if (arg != "all") {
                filterName = arg;
            }
        }

        // 3. Відкриття файлу
        std::ifstream file("database.txt");
        if (file.is_open()){
            std::string line;
            while (std::getline(file, line)){
                std::vector<std::string> data = split(line, '|');
                if (data.empty()) continue;

                // Фільтр за ім'ям пацієнта (data[2])
                if (!filterName.empty() && data[2] != filterName) {
                    continue; 
                }

                // Створення тимчасових об'єктів
                Doctor tempDoc(1, data[1], "General"); 
                Patient tempPat(100, data[2], "Unknown Address");

                // 4. Створення записів (З урахуванням ДАТИ)
                if (data[0] == "A" && data.size() >= 4) {
                    // Формат: A|Doctor|Patient|Date
                    history.push_back(new Appointment(tempDoc, tempPat, data[3]));
                }
                else if (data[0] == "P") {
                    // Для рецептів ми очікуємо дату в кінці
                    // Формат: P|Doctor|Patient|Drug|Dose|Date
                    std::string pDate = (data.size() >= 6) ? data[5] : "0000-00-00";
                    
                    if (data.size() >= 5) {
                        history.push_back(new Prescription(tempDoc, tempPat, data[3], data[4], pDate));
                    }
                }
            }
            file.close();
        }

        // 5. СОРТУВАННЯ (Якщо попросили)
        if (sortNeeded) {
            std::sort(history.begin(), history.end(), [](MedicalRecord* a, MedicalRecord* b) {
                return a->getDate() < b->getDate(); // Порівняння дат
            });
        }

        // 6. Вивід результату
        if (history.empty()) {
            std::cout << "Записів не знайдено." << std::endl;
        } else {
            std::cout << "--- RESPONSE START ---" << std::endl; 
            for (MedicalRecord* rec : history) {
                std::cout << rec->getDetails() << std::endl;
            }
        }
        
        // Очищення пам'яті
        for (MedicalRecord* rec : history) delete rec;
    }
    else if (command == "add") {
        if (argc < 5) {
            std::cout << "Error: Usage ./run_backend add <Doctor> <Patient> <Date>" << std::endl;
            return 1;
        }
        // Запис у кінець файлу
        std::ofstream file("database.txt", std::ios::app);
        if (file.is_open()) {
            file << "A|" << argv[2] << "|" << argv[3] << "|" << argv[4] << "\n";
            file.close();
            std::cout << "Success: Saved" << std::endl;
        }
    }
    else {
        std::cout << "Unknown command" << std::endl;
    }
    return 0;
}