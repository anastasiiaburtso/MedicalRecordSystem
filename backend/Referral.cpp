#include "Referral.h"

Referral::Referral(Doctor d, Patient p, std::string spec, std::string dateStr)
    : doctor(d), patient(p), targetSpecialty(spec), date(dateStr) {}

std::string Referral::getDetails() {
    return date + "|" + doctor.getName() + "|Направлення|Направлено до: " + targetSpecialty;
}

std::string Referral::getDate() {
    return date;
}