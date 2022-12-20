#include "../include/City.h"

City::City(std::string city, std::string country): city_(city), country_(country) {}

std::string City::getCity() const {
    return city_;
}

std::string City::getCoutry() const {
    return country_;
}

