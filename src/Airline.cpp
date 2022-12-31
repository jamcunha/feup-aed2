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

std::string Airline::getName() const {
    return name_;
}

std::string Airline::getCallsign() const {
    return callsign_;
}

std::string Airline::getCountry() const {
    return country_;
}

bool Airline::operator==(const Airline &airline) const {
    return code_ == airline.getCode();
}

