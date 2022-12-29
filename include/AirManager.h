#ifndef FEUP_AED2_AIRMANAGER_H
#define FEUP_AED2_AIRMANAGER_H

#include "Graph.h"
#include "Airline.h"

#include <list>
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

    std::list<Airport> getTraveledAirports(const std::string &source_airport, const std::string &target_airport);

    int getNumberOfFlights(const std::string &airport_code) const;

    std::list<Airline> getAirlinesFromAirport(const std::string &airport_code) const;
};

#endif //FEUP_AED2_AIRMANAGER_H

