#include "../include/Graph.h"
#include "../include/Utils.h"

#include <iostream>
#include <queue>

Graph::Graph(bool dir): has_dir(dir) {}

void Graph::shortestPath(const std::string &airport_code) {
    std::priority_queue<std::pair<std::string, double>> q;

    nodes[airport_code].src_distance = 0;
    nodes[airport_code].travel_from_src.clear();
    nodes[airport_code].travel_from_src.push_back(nodes[airport_code].airport);

    setUnvisited();
    for(auto &node: nodes) {
        if(node.first != airport_code) {
            node.second.src_distance = INF;
            node.second.travel_from_src.clear();
            q.push({node.first, node.second.src_distance});
        }
        q.push({ node.first, node.second.src_distance });
    }

    while(!q.empty()) {
        std::pair<std::string, double> u = q.top(); q.pop();

        Node& node = nodes[u.first];
        for(auto &e: node.adj) {
            if(wanted_airlines.size() != 0 && wanted_airlines.find(e.airline) == wanted_airlines.end())
                continue;
            double alt = node.src_distance + e.distance;
            Node &v = nodes[e.dest];
            if(alt < v.src_distance) {
                v.travel_from_src.clear();
                for(Airport &airport: node.travel_from_src)
                    v.travel_from_src.push_back(airport);
                v.travel_from_src.push_back(v.airport);
                v.src_distance = alt;
                q.push({ e.dest, alt });
            }
        }
    }
}

void Graph::addNode(const std::string &airport_code, const Airport &airport) {
    nodes.insert({ airport_code, { airport, {}, false, INF, std::list<Airport>() } });
}

void Graph::addEdge(const std::string& source_airport, const std::string& target_airport, const std::string& airline) {
    auto s_airport = nodes.find(source_airport);
    auto t_airport = nodes.find(target_airport);
    if(s_airport == nodes.end() || t_airport == nodes.end() || s_airport == t_airport) return;

    double distance = utils::haversine(s_airport->second.airport, t_airport->second.airport);

    s_airport->second.adj.push_back({ target_airport, airline, distance });

    if(!this->has_dir)
        t_airport->second.adj.push_back({ source_airport, airline, distance });
}

void Graph::setUnvisited() {
    for(auto &it: nodes) {
        it.second.visited = false;
    }
}

void Graph::dfs(const std::string &airport_code) {
    std::cout << nodes[airport_code].airport.getCode() << '\n';
    nodes[airport_code].visited = true;

    for(const auto &e: nodes[airport_code].adj) {
        Node& target_node = nodes[e.dest];

        if(!target_node.visited) {
            dfs(e.dest);
        }
    }
}

void Graph::bfs(const std::string &airport_code) {
    setUnvisited();

    std::queue<std::string> q; // queue of unvisited nodes
    q.push(airport_code);
    nodes[airport_code].visited = true;
    while(!q.empty()) {
        std::string u = q.front(); q.pop();

        Node& node = nodes[airport_code];
        std::cout << node.airport.getCode() << '\n';

        for(const auto &e: node.adj) {
            std::string w = e.dest;
            if(!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
}

double Graph::getShortestPath(const std::string &source_airport, const std::string &target_airport) {
    shortestPath(source_airport);
    return nodes[target_airport].src_distance;
}

std::list<Airport> Graph::getTraveledAirports(const std::string &source_airport, const std::string &target_airport) {
    shortestPath(source_airport);
    return nodes[target_airport].travel_from_src;
}

std::string Graph::findAirport(double latitude, double longitude){
    std::string code;
    double latitude_min=MAXFLOAT, longitude_min=MAXFLOAT;
    for (auto node: nodes) {
        if (utils::haversine(latitude,node.second.airport.getLatitude(),longitude,node.second.airport.getLongitude())<utils::haversine(latitude,latitude_min,longitude,longitude_min)){
            code = node.second.airport.getCode();
            latitude_min=node.second.airport.getLatitude();
            longitude_min=node.second.airport.getLongitude();
        }
    }
    return code;
}

std::list<std::string> Graph::findAirport_city(std::string city) {
    std::list<std::string> airports;
    for (auto node:nodes){
        if (node.second.airport.getCity()==city)
            airports.push_back(node.first);
    }
}

