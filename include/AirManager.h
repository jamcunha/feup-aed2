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
    bool how_to_fly;

    void readData();

public:
    AirManager();
    ~AirManager();

    Airport getAirport(const std::string &airport_code) const;
    
    Airline getAirline(const std::string &airline_code) const;

    double getDistance(const std::string &source_airport, const std::string &target_airport);

    std::list<std::list<std::pair<Airport,std::string>>> getTraveledAirports(const std::string &source_airport, const std::string &target_airport) const;

    std::list<std::list<std::pair<Airport,std::string>>> localCoordinates(double start_latitude, double start_longitude, double end_latitude, double end_longitude) const;

    std::list<std::list<std::pair<Airport, std::string>>> localCity(const std::string &start, const std::string &end) const;

    std::list<std::list<std::pair<Airport, std::string>>> localCoordinatesClosest(double start_latitude, double start_longitude, double end_latitude, double end_longitude) const;

    int getMinFlights(const std::string &source_airport, const std::string &target_airport);

    int getNumberOfFlights(const std::string &airport_code) const;

    std::list<Airline> getAirlinesFromAirport(const std::string &airport_code) const;

    std::list<Airport> getAirportsReached(const std::string &source_airport, int k);

    std::set<std::string> getCitiesReached(const std::string &source_airport, int k);

    std::set<std::string> getCountriesReached(const std::string &source_airport, int k);

    std::set<std::string> getArrivalAirport(const std::string &airport_code) const;

    std::set<std::string> getArrivalCities(const std::string &airport_code) const;

    std::set<std::string> getArrivalCountries(const std::string &airport_code) const;

    bool checkIfAirportExists(const std::string &airport_code) const;

    bool checkIfAirlineExists(const std::string &airline_code) const;

    bool addWantedAirline(const std::string &airline_code);

    bool removeWantedAirline(const std::string &airline_code);

    void clearWantedAirline();

    std::unordered_set<std::string> getWantedAirlines() const;

    std::list<std::string> findAirportByCity(const std::string &city) const;

    bool getHowToFly() const;
    void changeHowToFly();
};

#endif //FEUP_AED2_AIRMANAGER_H

