#include "../include/Utils.h"

double utils::haversine(double lat1, double lat2, double long1, double long2) {
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLong = (long2 - long1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = std::pow(sin(dLat / 2), 2) + std::pow(sin(dLong / 2), 2) * cos(lat1) * cos(lat2);
    double earth_rad = 6371;
    double c = 2 * asin(sqrt(a));

    return earth_rad * c;
}

double utils::haversine(Airport &source, Airport &target) {
    return haversine(source.getLatitude(), target.getLatitude(), source.getLongitude(), target.getLongitude());
}

