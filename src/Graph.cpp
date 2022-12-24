#include "../include/Graph.h"
#include "../include/Utils.h"

Graph::Graph(int num, bool dir): n(num), has_dir(dir) {}

void Graph::addNode(std::string airport_code, Airport &airport) {
    nodes.insert({ airport_code, { airport, {}, false } });
}

void Graph::addEdge(std::string source_airport, std::string target_airport) {
    auto s_airport = nodes.find(source_airport);
    auto t_airport = nodes.find(target_airport);

    if(s_airport == nodes.end() || t_airport == nodes.end() || s_airport == t_airport) return;

    double distance = utils::haversine(s_airport->second.airport, t_airport->second.airport);

    s_airport->second.adj.push_back({ target_airport, distance });

    if(!this->has_dir)
        t_airport->second.adj.push_back({ source_airport, distance });
}

