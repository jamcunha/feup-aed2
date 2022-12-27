#include "../include/Airline.h"

Airline::Airline(
    std::string code,
    std::string name,
    std::string callsign,
    std::string country
): code_(code),
    name_(name),
    callsign_(callsign),
    country_(country) {}

std::string Airline::getCode() const {
    return code_;
}

bool Airline::operator==(const Airline &airline) const {
    return code_ == airline.getCode();
}

