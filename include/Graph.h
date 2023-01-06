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
/**
 * Represents a Graph.
 */
class Graph {
private:
    /**
     * Represents the edges of the graph.
     */
    struct Edge {
        /**
         * @brief Destination Node
         */
        std::string dest;
        /**
         * @brief Airline in charge of the flight
         */
        std::string airline;
        /**
         * @brief Distance between two nodes.
         */
        double distance;
    };
    /**
     * Represents the content of each node.
     */
    struct Node {
        /**
         * @brief Airport
         */
        Airport airport;
        /**
         * @brief List of outgoing edges, to adjacent nodes.
         */
        std::list<Edge> adj;
        /**
         * @brief Verifies if the node has been visited on a previous search.
         * @details This variable set to True means that the node has been visited and False otherwise.
         */
        bool visited;
        /**
         * @brief Distance to the source node.
         * @details This can be used to find the shortest path to node.
         */
        double src_distance;
        /**
         * @brief A list that stores another list with all the airports and airlines from the source all the way to the target node.
         */
        std::list<std::list<std::pair<Airport,std::string>>> travel_from_src;
    };
    /**
     * @brief Variable that sets the Graph to be directed or undirected.
     * @details This variable set to True means the Graph is directed and False otherwise.
     */
    bool has_dir;
    /**
     * @brief A hash table.
     * @details When searching the Time Complexity O(1).
     */
    std::unordered_map<std::string, Node> nodes;
    /**
     * @brief Set of airlines favoured by the client.
     * @details Can be empty.
     */
    std::unordered_set<std::string> wanted_airlines;
    /**
     * @brief Find the shortest path using Dijkstra Algorithm.
     * @details Time Complexity - O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Code of the target Airport.
     */
    void shortestPath(const std::string &airport_code);

public:
    //"Constructers"
    /**
     * @brief Creates a new Graph.
     * @details The Graph is undirected by default.
     * @details To change it use Graph(true) in initialization.
     * @param dir
     */
    Graph(bool dir = false);
    /**
     * @brief Add a node to the Graph using the airport code as a key and the whole airport class as the value.
     * @param airport_code Airport's code
     * @param airport All of the airport information.
     */
    void addNode(const std::string &airport_code, const Airport &airport);
    /**
     * @brief Add an edge from a source airport to a target airport using their distance as the weight.
     * @param source_airport The source airport.
     * @param target_airport The target airport.
     * @param airline Distance between the two airports.
     */
    void addEdge(const std::string& source_airport, const std::string& target_airport, const std::string& airline);
    /**
     * @brief This function sets all the nodes to unvisited state.
     * @details Time Complexity - O(V).
     * @details V is the number of vertices/nodes.
     */
    void setUnvisited();
    /**
     * @brief Function used to do a Depth-First Search (aka DFS).
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport code to be searched.
     */
    void dfs(const std::string &airport_code);
    /**
     * @brief Function used to do a Breadth-First Search (aka BFS).
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport code to be searched.
     */
    void bfs(const std::string &airport_code);

    /**
     * @details Gets the Airport class.
     * @param airport_code Airport's code.
     * @return All of the airport information.
     */
    Airport getAirport(const std::string &airport_code) const;
    /**
     * Gets the minimum of flights needed to go from a source airport to a said target airport.
     * @param source_airport Source airport's code.
     * @param target_airport Target airport's code.
     * @return Lowest number of flights needed.
     */
    int getMinFlights(const std::string &source_airport, const std::string &target_airport);
    /**
     * @brief Gets a list of every traveled airport in a trip from a source airport to a target airport.
     * @details Uses the minimum amount of flights as a criteria.
     * @param source_airport Source airport's code.
     * @param target_airport Target airport's code.
     * @return List of all airports the client traveled through in a trip.
     */
    std::list<std::list<std::pair<Airport,std::string>>> getTraveledAirports(const std::string &source_airport, const std::string &target_airport);
    /**
     * @brief Search the airport located in fixed GPS coordinates.
     * @param latitude Latitude of the airport.
     * @param longitude Longitude of the airport.
     * @return Airport's code.
     */
    std::string findAirport(double latitude, double longitude);
    /**
     * @brief Search all the airports located in a city.
     * @param city City where the airports are located.
     * @return List of all the airports located within the city.
     */
    std::list<std::string> findAirportByCity(const std::string &city);
    /**
     * @brief Search the airport located in fixed GPS coordinates.
     * @param latitude Latitude of the airport.
     * @param longitude Longitude of the airport.
     * @return All of the airport information.
     */
    std::list<std::string> findAirports(double latitude, double longitude);
    /**
     * @brief Gets the number of kilometers traveled in a straight line from a source airport to a target airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param source_airport Source airport's code.
     * @param target_airport Target airport's code.
     * @return Number of kilometers traveled in a straight line between two airports.
     */
    double getShortestPath(const std::string &source_airport, const std::string &target_airport);
    /**
     * @brief
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param source_airport Source airport's code.
     * @param target_airport Target airport's code.
     * @return A list that stores another list with all the airports and airlines traveled from the source airport all the way to the target airport.
     */
    std::list<std::list<std::pair<Airport,std::string>>> getTraveledAirportsByDistance(const std::string &source_airport, const std::string &target_airport);
    /**
     * @brief Gets the total number of flights connected to an airport.
     * @param airport_code Airport's code.
     * @return Total number of flights from a single airport.
     */
    int getNumberOfFlights(const std::string &airport_code) const;
    /**
     * @brief Gets all of the airlines connected to an airport.
     * @param airport_code Airport's code.
     * @return Set with airlines connected to a certain airport.
     */
    std::set<std::string> getAirlinesFromAirport(const std::string &airport_code) const;
    /**
     * @brief Gets all airports that can be reached from a source airport in a fixed number of flights.
     * @param source_airport Source airport's code.
     * @param k Number of flights.
     * @return List of airports reachable within a "k" number of flights.
     */
    std::list<Airport> getAirportsReached(const std::string &source_airport, int k);
    /**
     * @brief Gets all cities that can be reached from a source airport in a fixed number of flights.
     * @param source_airport Source airport's code.
     * @param k Number of flights.
     * @return List of cities reachable within a "k" number of flights.
     */
    std::set<std::string> getCitiesReached(const std::string &source_airport, int k);
    /**
     * @brief Gets all countries that can be reached from a source airport in a fixed number of flights.
     * @param source_airport Source airport's code.
     * @param k Number of flights.
     * @return List of countries reachable within a "k" number of flights.
     */
    std::set<std::string> getCountriesReached(const std::string &source_airport, int k);
    /**
     * @brief Gets all cities that can be reached with 1 flight from a source airport.
     * @param airport_code Airport's code.
     * @return List of cities reachable within 1 flight.
     */
    std::set<std::string> getArrivalCities(const std::string &airport_code) const;
    /**
     * @brief Gets all countries that can be reached with 1 flight from a source airport.
     * @param airport_code Airport's code.
     * @return List of countries reachable within 1 flight.
     */
    std::set<std::string> getArrivalCountries(const std::string &airport_code) const;
};

#endif //FEUP_AED2_GRAPH_H

