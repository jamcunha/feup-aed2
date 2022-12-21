#include "../include/Graph.h"
#include "../include/Utils.h"

Graph::Graph(int num, bool dir): n(num), has_dir(dir) {}

void Graph::addNode(std::string airport_code, Airport &airport) {
    nodes.insert({airport_code, {airport, {}, false}});
}

void Graph::addEdge(Flight &flight) {
    auto s_airport = nodes.find(flight.getSource().getCode());
    auto t_airport = nodes.find(flight.getTarget().getCode());

    if(s_airport == nodes.end() || t_airport == nodes.end() || s_airport == t_airport) return;

    double distance = utils::haversine(s_airport->second.airport, t_airport->second.airport);

    s_airport->second.adj.push_back({flight, distance});

    if(!this->has_dir)
        t_airport->second.adj.push_back({Flight(flight.getTarget(), flight.getSource(), flight.getAirline()), distance});
}

