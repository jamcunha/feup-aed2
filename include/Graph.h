#ifndef FEUP_AED2_GRAPH_H
#define FEUP_AED2_GRAPH_H

#include "Airport.h"

#include <list>
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
        std::list<Airport> travel_from_src; // vector that stores all airports traveler from source to target in order
        // maybe could just store the code
    };

    bool has_dir; // false: undirected; true: directed
    std::unordered_map<std::string, Node> nodes; // A hash table to have O(1) search { airport_code, node }
    std::unordered_set<std::string> wanted_airlines; // use if exists preference in airline(s)

    // Find the shortest path using dijkstra algorithm - O(|E|log(|V|))
    // maybe make this public and getShortestPath just return the src_distance
    void shortestPath(const std::string &airport_code);

public:
    // Constructor: nr of nodes and direction (default: undirected)
    // num = nr of airports
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

    double getShortestPath(const std::string &source_airport, const std::string &target_airport);

    std::list<Airport> getTraveledAirports(const std::string &source_airport, const std::string &target_airport);

    std::string findAirport(double latitude, double longitude);

    std::list<std::string> findAirport_city(const std::string &city);
};

#endif //FEUP_AED2_GRAPH_H

