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
#include "Referral.h"


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
    if (argc < 2) {
        std::cout << "Error: No command provided" << std::endl;
        return 1; 
    }

    std::string command = argv[1];

    std::string dbPath = "backend/database.txt";

    if (command == "test") {
        std::cout << "Backend is online." << std::endl;
    }
    else if (command == "history") {
        std::vector<MedicalRecord*> history;
        std::string filterName = "";
        std::string sortOrder = "none"; 

       
        for (int i = 2; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "sort_asc") {
                sortOrder = "asc"; 
            } else if (arg == "sort_desc") {
                sortOrder = "desc"; 
            } else if (arg == "sort") {
                sortOrder = "asc"; 
            } else if (arg != "all" && arg != "none") {
                filterName = arg;
            }
        }

        
        std::ifstream file(dbPath);
        if (file.is_open()){
            std::string line;
            while (std::getline(file, line)){
                std::vector<std::string> data = split(line, '|');
                if (data.empty()) continue;

                 
                if (!filterName.empty() && data[2] != filterName) {
                    continue; 
                }

                
                Doctor tempDoc(1, data[1], "General"); 
                Patient tempPat(100, data[2], "Unknown Address");

                if (data[0] == "A" && data.size() >= 4) {
                    history.push_back(new Appointment(tempDoc, tempPat, data[3]));
                }
                else if (data[0] == "P" && data.size() >= 5) {
                    std::string pDate = (data.size() >= 6) ? data[5] : "0000-00-00";
                    history.push_back(new Prescription(tempDoc, tempPat, data[3], data[4], pDate));
                }
                else if (data[0] == "R" && data.size() >= 5) {
                    history.push_back(new Referral(tempDoc, tempPat, data[3], data[4]));
                }
            }
            file.close();
        }else {
            file.open("database.txt");
            
            if (file.is_open()){
                std::string line;
                while (std::getline(file, line)){
                    std::vector<std::string> data = split(line, '|');
                    if (data.empty()) continue;

                    if (!filterName.empty() && data[2] != filterName) {
                        continue; 
                    }

                    Doctor tempDoc(1, data[1], "General"); 
                    Patient tempPat(100, data[2], "Unknown Address");

                    if (data[0] == "A" && data.size() >= 4) {
                        history.push_back(new Appointment(tempDoc, tempPat, data[3]));
                    }
                    else if (data[0] == "P" && data.size() >= 5) {
                        std::string pDate = (data.size() >= 6) ? data[5] : "0000-00-00";
                        history.push_back(new Prescription(tempDoc, tempPat, data[3], data[4], pDate));
                    }
                    else if (data[0] == "R" && data.size() >= 5) {
                        history.push_back(new Referral(tempDoc, tempPat, data[3], data[4]));
                    }
                }
                file.close();
            } else {
                std::cout << "Error: Could not open database file (checked " << dbPath << " and database.txt)" << std::endl;
            }
        }

        //СОРТУВАННЯ
        if (sortOrder == "asc") {
            std::sort(history.begin(), history.end(), [](MedicalRecord* a, MedicalRecord* b) {
                return a->getDate() < b->getDate(); 
            });
        } else if (sortOrder == "desc") {
            std::sort(history.begin(), history.end(), [](MedicalRecord* a, MedicalRecord* b) {
                return a->getDate() > b->getDate(); 
            });
        }

    
        if (history.empty()) {
            std::cout << "Записів не знайдено." << std::endl;
        } else { 
            for (MedicalRecord* rec : history) {
                std::cout << rec->getDetails() << std::endl;
            }
        }
        
        
        for (MedicalRecord* rec : history) delete rec;
    }
    else if (command == "add") {
        std::ofstream file("database.txt", std::ios::app);
        
        if (file.is_open()) {
            std::string type = argv[2];

            // НАПРАВЛЕННЯ (R)
            if (type == "R") {
                if (argc >= 7) {
                    file << "R|" << argv[3] << "|" << argv[4] << "|" << argv[5] << "|" << argv[6] << "\n";
                }
            } 
            //РЕЦЕПТ (P)
            else if (type == "P") {
                if (argc >= 8) {
                    file << "P|" << argv[3] << "|" << argv[4] << "|" << argv[5] << "|" << argv[6]<< "|" << argv[7] << "\n";
                }
                else {
                    std::cout << "Error: Not enough args for Prescription" << std::endl;
                }
            }
            //ЗВИЧАЙНИЙ ЗАПИС (A)
            else {
                if (argc >= 5) {
                    file << "A|" << argv[2] << "|" << argv[3] << "|" << argv[4] << "\n";
                }
            }
            
            file.close();
            std::cout << "Success: Saved" << std::endl;
        } else {
            std::cout << "Error: Could not open file" << std::endl;
        }
    }
    else {
        std::cout << "Unknown command" << std::endl;
    }
    return 0;
}