#include "../include/Graph.h"
#include "../include/Utils.h"

#include <iostream>
#include <queue>

Graph::Graph(int num, bool dir): n(num), has_dir(dir) {}

void Graph::addNode(const std::string &airport_code, const Airport &airport) {
    nodes.insert({ airport_code, { airport, {}, false } });
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

