#ifndef FEUP_AED2_GRAPH_H
#define FEUP_AED2_GRAPH_H

#include "Airport.h"
#include "Airline.h"
#include "Utils.h"

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
     * @details When searching the Time Complexity is O(1).
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
    //"Constructors"
    /**
     * @brief Creates a new Graph.
     * @details The Graph is undirected by default.
     * @details To change it use Graph(true) in initialization.
     * @details Constructor of the Graph class.
     * @param dir
     */
    Graph(bool dir = false);
    /**
     * @brief Add a node to the Graph using the airport code as a key and the whole airport class as the value.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code
     * @param airport All of the airport information.
     */
    void addNode(const std::string &airport_code, const Airport &airport);
    /**
     * @brief Add an edge from a source airport to a target airport using their distance as the weight.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
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
     * @brief Gets the Airport class.
     * @details Time Complexity - O(1).
     * @param airport_code Airport's code.
     * @return All of the airport information.
     */
    Airport getAirport(const std::string &airport_code) const;
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
     * @brief Gets a list of every traveled airport in a trip from a source airport to a target airport.
     * @details Time Complexity - O(|V| + |E|).
     * @details Uses the minimum amount of flights as a criteria.
     * @param source_airport Source airport's code.
     * @param target_airport Target airport's code.
     * @return List of all airports the client can travel through in a trip.
     */
    std::list<std::list<std::pair<Airport,std::string>>> getTraveledAirports(const std::string &source_airport, const std::string &target_airport);
    /**
     * @brief Search the airport located in fixed GPS coordinates.
     * @details Time Complexity - O(V log(n)).
     * @details V is the number of vertices/nodes.
     * @param latitude Latitude of the airport.
     * @param longitude Longitude of the airport.
     * @return Airport's code.
     */
    std::string findAirport(double latitude, double longitude);
    /**
     * @brief Search all the airports located in a city.
     * @details Time Complexity - O(V).
     * @details V is the number of vertices/nodes.
     * @param city City where the airports are located.
     * @return List of all the airports located within the city.
     */
    std::list<std::string> findAirportByCity(const std::string &city);
    /**
     * @brief Search the airport located within a certain distance from fixed GPS coordinates.
     * @details Time Complexity - O(V log(n)).
     * @details V is the number of vertices/nodes.
     * @param latitude Latitude of the airport.
     * @param longitude Longitude of the airport.
     * @param dist Distance where airports can be.
     * @return All of the airport information.
     */
    std::list<std::string> findAirports(double latitude, double longitude, int dist);
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
     * @brief Gets the list of airports and airlines traveled through in a trip between 2 airports.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param source_airport Source airport's code.
     * @param target_airport Target airport's code.
     * @return A list that stores another list with all the airports and airlines traveled from the source airport all the way to the target airport.
     */
    std::list<std::list<std::pair<Airport,std::string>>> getTraveledAirportsByDistance(const std::string &source_airport, const std::string &target_airport);
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
     * @return Set with all airlines(airline's code) connected to a certain airport.
     */
    std::set<std::string> getAirlinesFromAirport(const std::string &airport_code) const;
    /**
     * @brief Gets all airports that can be reached from a source airport in a fixed number of flights.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param source_airport Source airport's code.
     * @param k Number of flights.
     * @return List of airports reachable within a "k" number of flights.
     */
    std::list<Airport> getAirportsReached(const std::string &source_airport, int k);
    /**
     * @brief Gets all cities that can be reached from a source airport in a fixed number of flights.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param source_airport Source airport's code.
     * @param k Number of flights.
     * @return List of cities reachable within a "k" number of flights.
     */
    std::set<std::string> getCitiesReached(const std::string &source_airport, int k);
    /**
     * @brief Gets all countries that can be reached from a source airport in a fixed number of flights.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param source_airport Source airport's code.
     * @param k Number of flights.
     * @return List of countries reachable within a "k" number of flights.
     */
    std::set<std::string> getCountriesReached(const std::string &source_airport, int k);
    /**
     * @brief Gets all airports that can be reached with 1 flight from a source airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @return List of airports reachable within 1 flight.
     */
    std::set<std::string> getArrivalAirports(const std::string &airport_code) const;
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
    /**
     * @brief Checks if airport exists in nodes hash table.
     * @details Time Complexity- O(V).
     * @details V is the number of vertices/nodes.
     * @param airport_code Airport's code.
     * @return True-If the airport exists.
     * @return False-If the airport doesn't exist.
     */
    bool checkIfAirportExists(const std::string &airport_code) const;
    /**
     * @brief Adds a airline to the favourite airlines list.
     * @details Time Complexity- O(log(n)).
     * @details V is the number of vertices/nodes.
     * @param airline_code Airline's code.
     */
    void addWantedAirline(const std::string &airline_code);
    /**
     * @brief Removes the airline from the favourite airlines list.
     * @details Time Complexity- O(n).
     * @param airline_code Airline's code.
     * @return True-If it was successfully removed.
     * @return True-If the airline selected was not in the favourites list.
     */
    bool removeWantedAirline(const std::string &airline_code);
    /**
     * @brief Clears the favourite airlines list.
     * @details Time Complexity- O(n).
     */
    void clearWantedAirline();
    /**
     * @brief Gets the full list of favoured airlines.
     * @details Time Complexity - O(1).
     * @return Set of all the airlines included in the favourite list.
     */
    std::unordered_set<std::string> getWantedAirlines() const;
    /**
     * @brief Gives the size of the Graph nodes.
     * @details The number of nodes is equal to the number of airports.
     * @details Time Complexity- O(1).
     * @return Total number of nodes in the Graph.
     */
    int size_Nodes();
    /**
     * @brief Gives the size of the Graph edges.
     * @details The number of edges is equal to the number of flights.
     * @details Time Complexity- O(V).
     * @details V is the number of vertices/nodes.
     * @return Total number of edges in the Graph.
     */
    int size_Flights();
    /**
     * @brief Function used to help calculate the diameter of the graph.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport code to be searched.
     */
    void bfs_diameter(const std::string &airport_code);
    /**
     * @brief Gets the diameter from every flight.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @return Diameter.
     */
    int Diameter();
    /**
     * Gets de top "k" of flights by distance traveled.
     * @param k Number of flights to be ranked.
     * @return Set of the longest flights.
     */
    std::multiset<std::pair<std::string,int>,utils::CompareDistance> top_flights(int k);
};

#endif //FEUP_AED2_GRAPH_H

