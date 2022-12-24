#include "../include/Airport.h"

Airport::Airport(
    std::string code,
    std::string name,
    std::string city,
    std::string country,
    double latitude,
    double longitude
): code_(code),
    name_(name),
    city_(city),
    country_(country),
    latitude_(latitude),
    longitude_(longitude) {}

std::string Airport::getCode() const {
    return code_;
}

double Airport::getLatitude() const {
    return latitude_;
}

double Airport::getLongitude() const {
    return longitude_;
}

