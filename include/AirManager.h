#ifndef FEUP_AED2_AIRMANAGER_H
#define FEUP_AED2_AIRMANAGER_H

#include "Graph.h"
#include "Airline.h"

#include <list>
#include <unordered_set>

class AirManager {
private:
    struct hashAirline {
        size_t operator() (const Airline &airline) const {
            std::hash<std::string> hash;
            return hash(airline.getCode());
        }
    };

    Graph* airports_;
    std::unordered_set<Airline, hashAirline> airlines_;
    std::unordered_set<std::string> cities_;

    void readData();

public:
    AirManager();
    ~AirManager();

    double getDistance(const std::string &source_airport, const std::string &target_airport);

    std::list<Airport> getTraveledAirports(const std::string &source_airport, const std::string &target_airport);

    void local_coordenates();

    void local_city();

    void local_coordenates_closest();
};

#endif //FEUP_AED2_AIRMANAGER_H

