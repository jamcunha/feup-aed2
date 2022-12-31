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

std::string Airport::getName() const {
    return name_;
}

std::string Airport::getCity() const {
    return city_;
}

std::string Airport::getCountry() const {
    return country_;
}

double Airport::getLatitude() const {
    return latitude_;
}

double Airport::getLongitude() const {
    return longitude_;
}

bool Airport::operator==(const Airport &airport) const {
    return code_ == airport.getCode();
}
