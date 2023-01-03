#ifndef FEUP_AED2_GRAPH_H
#define FEUP_AED2_GRAPH_H

#include "Airport.h"
#include "Airline.h"

#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <limits>

#define INF std::numeric_limits<double>::max()

class Graph {
private:
    struct Edge {
        std::string dest; // Destination Node
        std::string airline; // Airline of the flight
        double distance; // Distance between nodes
    };

    struct Node {
        Airport airport; // Airport
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited; // Verify if the node has been visited on a search
        double src_distance; // Distance to source node (used to find the shortest path to node)
        std::list<std::list<std::pair<Airport,std::string>>> travel_from_src; // list that stores lists of airports and airline taken from source to target
    };

    bool has_dir; // false: undirected; true: directed
    std::unordered_map<std::string, Node> nodes; // A hash table to have O(1) search { airport_code, node }
    std::unordered_set<std::string> wanted_airlines; // use if exists preference in airline(s)

    // Find the shortest path using dijkstra algorithm - O(|E|log(|V|))
    // may be used for a extra feature
    void shortestPath(const std::string &airport_code);

public:
    // Constructor: nr of nodes and direction (default: undirected)
    Graph(bool dir = false);

    // Add a node to the graph using an airport code as key and the airport as value
    void addNode(const std::string &airport_code, const Airport &airport);

    // Add an edge from an airport to another with their distance as the weight
    void addEdge(const std::string& source_airport, const std::string& target_airport, const std::string& airline);

    // Set all nodes to unvisited
    void setUnvisited();

    // Depth-First Search - O(|V| + |E|)
    void dfs(const std::string &airport_code);

    // Breadth-First Search - O(|V| + |E|)
    void bfs(const std::string &airport_code);

    // Get a airport
    Airport getAirport(const std::string &airport_code) const;

    // Get minimum of flights needed to go from a source airport to a target airport
    int getMinFlights(const std::string &source_airport, const std::string &target_airport);

    // Criteria: minimum number of flights
    std::list<std::list<std::pair<Airport,std::string>>> getTraveledAirports(const std::string &source_airport, const std::string &target_airport);

    std::string findAirport(double latitude, double longitude);

    std::list<std::string> findAirportByCity(const std::string &city);

    std::list<std::string> findAirports(double latitude, double longitude);

    // Get number of kilometers traveled in a straight line from a source airport to a target airport
    double getShortestPath(const std::string &source_airport, const std::string &target_airport);

    // Criteria: minimum distance traveled
    std::list<std::list<std::pair<Airport,std::string>>> getTraveledAirportsByDistance(const std::string &source_airport, const std::string &target_airport);

    // Number of existing flights from an airport
    int getNumberOfFlights(const std::string &airport_code) const;

    // Get all airlines present in an airport
    std::set<std::string> getAirlinesFromAirport(const std::string &airport_code) const;

    // Get all airports that can be reached from a source airport in a number k of flights
    std::list<Airport> getAirportsReached(const std::string &source_airport, int k);

    // Get all cities that can be reached from a source airport in a number k of flights
    std::set<std::string> getCitiesReached(const std::string &source_airport, int k);

    // Get all countries that can be reached from a source airport in a number k of flights
    std::set<std::string> getCountriesReached(const std::string &source_airport, int k);

    // Get airports that can be reached with 1 flight from a source airport
    std::set<std::string> getArrivalAirports(const std::string &airport_code) const;

    // Get cities that can be reached with 1 flight from a source airport
    std::set<std::string> getArrivalCities(const std::string &airport_code) const;

    // Get countries that can be reached with 1 flight from a source airport
    std::set<std::string> getArrivalCountries(const std::string &airport_code) const;

    // Check if airport exists in nodes hash table
    bool checkIfAirportExists(const std::string &airport_code) const;

    void addWantedAirline(const std::string &airline_code);

    bool removeWantedAirline(const std::string &airline_code);

    void clearWantedAirline();
};

#endif //FEUP_AED2_GRAPH_H

