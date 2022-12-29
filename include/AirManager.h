#ifndef FEUP_AED2_AIRMANAGER_H
#define FEUP_AED2_AIRMANAGER_H

#include "Graph.h"
#include "Airline.h"

#include <vector>
#include <unordered_set>

class AirManager {
private:
    Graph* airports_;
    std::vector<Airline> airlines_;
    std::unordered_set<std::string> cities_;

    void readData();

public:
    AirManager();
    ~AirManager();

    double getDistance(const std::string &source_airport, const std::string &target_airport);

    std::vector<Airport> getTraveledAirports(const std::string &source_airport, const std::string &target_airport);
};

#endif //FEUP_AED2_AIRMANAGER_H

