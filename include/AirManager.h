#ifndef FEUP_AED2_AIRMANAGER_H
#define FEUP_AED2_AIRMANAGER_H

#include "Graph.h"
#include "Airline.h"

#include <list>
#include <set>
#include <unordered_set>
#include <unordered_map>
/**
 * Represents the Manager of the air traffic.
 */
class AirManager {
private:
    /**
     * @brief Graph with all the information of the air traffic, airports and flights.
     */
    Graph* airports_;
    /**
     * @brief Stores all the airlines, connecting them to their code.
     */
    std::unordered_map<std::string, Airline> airlines_;
    /**
     * @brief A set used to fill with all the cities with airports.
     */
    std::unordered_set<std::string> cities_;
    /**
     * @brief Reads all the data saved in the files and stores them in the correct structures.
     * @details Time Complexity - O(n^3).
     */
    void readData();

public:
    //"Constructers"
    /**
     * @brief Creates a new manager.
     * @details Constructor of the AirManager class.
     * @details Creates a new directed Graph and reads all the data from the files.
     */
    AirManager();
    /**
     * @brief Deletes the current manager.
     * @details Destructor of the AirManager class.
     * @details Deletion of the current airports and flights Graph.
     */
    ~AirManager();
    /**
     * @brief Gets the distance in kilometers between 2 airports.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param source_airport Source airport´s code.
     * @param target_airport Target airport's code.
     * @return Number of kilometers traveled in a straight line between two airports.
     */
    //"Getters"
    double getDistance(const std::string &source_airport, const std::string &target_airport);
    /**
     * @brief Gets a list of every traveled airport in a trip from a source airport to a target airport.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param source_airport Source airport's code.
     * @param target_airport Target airport's code.
     * @return List of all airports the client can travel through in a trip.
     */
    std::list<std::list<std::pair<Airport,std::string>>> getTraveledAirports(const std::string &source_airport, const std::string &target_airport);
    /**
     * @brief Gets a list of every traveled airport in a trip from a source airport to a target airport using local GPS coordinates as a reference.
     * @details Time Complexity - O(n^2 (|V|+|E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param start_longitude Source airport's longitude.
     * @param start_latitude Source airport's latitude.
     * @param end_longitude Target airport's longitude.
     * @param end_latitude Target airport's latitude.
     * @return List of all airports the client can travel through in a trip.
     */
    std::list<std::list<std::pair<Airport, std::string>>> localCoordinates(double start_longitude, double start_latitude, double end_longitude, double end_latitude);
    /**
     * @brief Gets a list of every traveled airport in a trip from a source airport to a target airport using both the host cities as reference.
     * @details Time Complexity - O(n^2 (|V|+|E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param start Source airport's city.
     * @param end Target airport's city.
     * @return List of all airports the client can travel through in a trip.
     */
    std::list<std::list<std::pair<Airport, std::string>>> localCity(std::string start, std::string end);
    /**
     * @brief Gets a list of every traveled airport in a trip from a source airport to a target airport using inputted GPS coordinates as reference.
     * @details Because inputting coordinates can be too exact, this function helps the user finding the closest airports to both coordinates.
     * @details Time Complexity - O(V log(n)).
     * @param start_longitude Longitude selected by the client.
     * @param start_latitude Latitude selected by the client.
     * @param end_longitude Longitude selected by the client.
     * @param end_latitude Latitude selected by the client.
     * @return List of all airports the client can travel through in a trip.
     */
    std::list<std::list<std::pair<Airport, std::string>>> localCoordinatesClosest(double start_longitude, double start_latitude, double end_longitude, double end_latitude);
    /**
     * Gets the minimum of flights needed to go from a source airport to a said target airport.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param source_airport Source airport's code.
     * @param target_airport Target airport's code.
     * @return Lowest number of flights needed.
     */
    int getMinFlights(const std::string &source_airport, const std::string &target_airport);
    /**
     * @brief Gets the total number of flights connected to an airport.
     * @details Time Complexity - O(1).
     * @param airport_code Airport's code.
     * @return Total number of flights from a single airport.
     */
    int getNumberOfFlights(const std::string &airport_code) const;
    /**
     * @brief Gets all of the airlines connected to an airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @return Set with all airlines connected to a certain airport.
     */
    std::list<Airline> getAirlinesFromAirport(const std::string &airport_code) const;
    /**
     * @brief Gets all cities that can be reached with 1 flight from a source airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @return List of cities reachable within 1 flight.
     */
    std::set<std::string> getArrivalCities(const std::string &airport_code) const;
    /**
     * @brief Gets all countries that can be reached with 1 flight from a source airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @return List of countries reachable within 1 flight.
     */
    std::set<std::string> getArrivalCountries(const std::string &airport_code) const;
};

#endif //FEUP_AED2_AIRMANAGER_H

