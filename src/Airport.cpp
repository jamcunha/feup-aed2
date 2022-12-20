#include "../include/Airport.h"

Airport::Airport(
    std::string code,
    std::string name,
    City &city,
    double latitude,
    double longitude
): code_(code),
    name_(name),
    city_(city),
    latitude_(latitude),
    longitude_(longitude) {}

