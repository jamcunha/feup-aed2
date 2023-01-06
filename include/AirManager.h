#ifndef FEUP_AED2_AIRMANAGER_H
#define FEUP_AED2_AIRMANAGER_H

#include "Graph.h"
#include "Airline.h"

#include <list>
#include <set>
#include <unordered_set>
#include <unordered_map>
/**
 *
 */
class AirManager {
private:
    /**
     *
     */
    Graph* airports_;
    /**
     *
     */
    std::unordered_map<std::string, Airline> airlines_;
    /**
     *
     */
    std::unordered_set<std::string> cities_;
    /**
     *
     */
    void readData();

public:
    //"Constructers"
    /**
     *
     */
    AirManager();
    /**
     *
     */
    ~AirManager();
    /**
     *
     * @param source_airport
     * @param target_airport
     * @return
     */
    //"Getters"
    double getDistance(const std::string &source_airport, const std::string &target_airport);
    /**
     *
     * @param source_airport
     * @param target_airport
     * @return
     */
    std::list<std::list<std::pair<Airport,std::string>>> getTraveledAirports(const std::string &source_airport, const std::string &target_airport);
    /**
     *
     * @param start_longitude
     * @param start_latitude
     * @param end_longitude
     * @param end_latitude
     * @return
     */
    std::list<std::list<std::pair<Airport, std::string>>> localCoordinates(double start_longitude, double start_latitude, double end_longitude, double end_latitude);
    /**
     *
     * @param start
     * @param end
     * @return
     */
    std::list<std::list<std::pair<Airport, std::string>>> localCity(std::string start, std::string end);
    /**
     *
     * @param start_longitude
     * @param start_latitude
     * @param end_longitude
     * @param end_latitude
     * @return
     */
    std::list<std::list<std::pair<Airport, std::string>>> localCoordinatesClosest(double start_longitude, double start_latitude, double end_longitude, double end_latitude);
    /**
     *
     * @param source_airport
     * @param target_airport
     * @return
     */
    int getMinFlights(const std::string &source_airport, const std::string &target_airport);
    /**
     *
     * @param airport_code
     * @return
     */
    int getNumberOfFlights(const std::string &airport_code) const;
    /**
     *
     * @param airport_code
     * @return
     */
    std::list<Airline> getAirlinesFromAirport(const std::string &airport_code) const;
    /**
     *
     * @param airport_code
     * @return
     */
    std::set<std::string> getArrivalCities(const std::string &airport_code) const;
    /**
     *
     * @param airport_code
     * @return
     */
    std::set<std::string> getArrivalCountries(const std::string &airport_code) const;
};

#endif //FEUP_AED2_AIRMANAGER_H

