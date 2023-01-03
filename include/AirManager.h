#ifndef FEUP_AED2_AIRMANAGER_H
#define FEUP_AED2_AIRMANAGER_H

#include "Graph.h"
#include "Airline.h"

#include <list>
#include <set>
#include <unordered_set>
#include <unordered_map>

class AirManager {
private:
    Graph* airports_;
    std::unordered_map<std::string, Airline> airlines_;
    std::unordered_set<std::string> cities_;

    void readData();

public:
    AirManager();
    ~AirManager();

    double getDistance(const std::string &source_airport, const std::string &target_airport);

    std::list<std::list<std::pair<Airport,std::string>>> getTraveledAirports(const std::string &source_airport, const std::string &target_airport);
    
    std::list<std::list<std::pair<Airport, std::string>>> localCoordinates(double start_longitude, double start_latitude, double end_longitude, double end_latitude);

    std::list<std::list<std::pair<Airport, std::string>>> localCity(std::string start, std::string end);

    std::list<std::list<std::pair<Airport, std::string>>> localCoordinatesClosest(double start_longitude, double start_latitude, double end_longitude, double end_latitude);

    int getMinFlights(const std::string &source_airport, const std::string &target_airport);

    int getNumberOfFlights(const std::string &airport_code) const;

    std::list<Airline> getAirlinesFromAirport(const std::string &airport_code) const;

    std::set<std::string> getArrivalCities(const std::string &airport_code) const;

    std::set<std::string> getArrivalCountries(const std::string &airport_code) const;
};

#endif //FEUP_AED2_AIRMANAGER_H

