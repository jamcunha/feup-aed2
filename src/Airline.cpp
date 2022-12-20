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

