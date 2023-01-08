#include "../include/Graph.h"
#include "../include/Utils.h"

#include <iostream>
#include <queue>

Graph::Graph(bool dir): has_dir(dir) {}

// used in priority queue used in dijkstra algorithm
struct CompareDistance {
    bool operator()(std::pair<std::string, double> const &n1, std::pair<std::string, double> const &n2) {
        return n1.second>n2.second;
    }
};

void Graph::shortestPath(const std::string &airport_code) {
    std::priority_queue<std::pair<std::string, double>,std::vector<std::pair<std::string, double>>, CompareDistance> q;

    setUnvisited();
    nodes[airport_code].src_distance = 0;
    nodes[airport_code].travel_from_src.push_back({{nodes[airport_code].airport,""}});

    for(auto &node: nodes) {
        if(node.first != airport_code)
            node.second.src_distance = INF;
        else
            q.push({ node.first, node.second.src_distance });
    }

    while(!q.empty()) {
        std::pair<std::string, double> u = q.top(); q.pop();
        Node& node = nodes[u.first];
        for(auto &e: node.adj) {
            if(!wanted_airlines.empty() && wanted_airlines.find(e.airline) == wanted_airlines.end())
                continue;
            double alt = node.src_distance + e.distance;
            Node &v = nodes[e.dest];
            if(alt < v.src_distance) {
                v.travel_from_src.clear();
                for(auto n : node.travel_from_src) {
                    n.push_back({v.airport,e.airline});
                    v.travel_from_src.push_back(n);
                }
                v.src_distance = alt;
                q.push({ e.dest, alt });
            }
            else if (alt<INF && alt == v.src_distance ){
                for(auto n : node.travel_from_src) {
                    n.push_back({v.airport,e.airline});
                    v.travel_from_src.push_back(n);
                }
            }
        }
    }
}

void Graph::addNode(const std::string &airport_code, const Airport &airport) {
    nodes.insert({ airport_code, { airport, {}, false, INF, std::list<std::list<std::pair<Airport,std::string>>>() } });//n
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
        it.second.travel_from_src.clear();
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
    nodes[airport_code].travel_from_src.push_back({ { nodes[airport_code].airport, "" } });

    while(!q.empty()) {
        std::string u = q.front(); q.pop();

        Node& node = nodes[u];
        // std::cout << node.airport.getCode() << '\n';

        for(const auto &e: node.adj) {
            if(!wanted_airlines.empty() && wanted_airlines.find(e.airline) == wanted_airlines.end())
                continue;
            std::string w = e.dest;

            if(!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                for(auto n: node.travel_from_src) {
                    n.push_back({nodes[w].airport, e.airline});
                    nodes[w].travel_from_src.push_back(n);
                }
            }
            else if (node.travel_from_src.front().size()+1==nodes[w].travel_from_src.front().size()){
                bool flag = true;
                for (auto n : nodes[w].travel_from_src) {
                    auto it = n.end();
                    std::advance(it,-2);
                    if (it->first==node.airport) {
                        flag= false;
                        break;
                    }
                }
                if (!flag) continue;
                for(auto n: node.travel_from_src) {
                    n.push_back({nodes[w].airport,e.airline});
                    nodes[w].travel_from_src.push_back(n);
                }
            }
        }
    }
}

Airport Graph::getAirport(const std::string &airport_code) const {
    return nodes.at(airport_code).airport;//n
}

int Graph::getMinFlights(const std::string &source_airport, const std::string &target_airport) {
    bfs(source_airport);
    return nodes[target_airport].travel_from_src.front().size() - 1;
}

std::list<std::list<std::pair<Airport,std::string>>> Graph::getTraveledAirports(const std::string &source_airport, const std::string &target_airport) {
    bfs(source_airport);
    return nodes[target_airport].travel_from_src;
}

double Graph::getShortestPath(const std::string &source_airport, const std::string &target_airport) {
    shortestPath(source_airport);
    return nodes.at(target_airport).src_distance;
}

std::list<std::list<std::pair<Airport,std::string>>> Graph::getTraveledAirportsByDistance(const std::string &source_airport, const std::string &target_airport) {
    shortestPath(source_airport);
    return nodes[target_airport].travel_from_src;
}

std::string Graph::findAirport(double latitude, double longitude){
    std::string code;
    double latitude_min=MAXFLOAT, longitude_min=MAXFLOAT;
    for (auto node: nodes) {//V
        if (utils::haversine(latitude,node.second.airport.getLatitude(),longitude,node.second.airport.getLongitude())<utils::haversine(latitude,latitude_min,longitude,longitude_min)) {//log(n)
            code = node.second.airport.getCode();//1
            latitude_min=node.second.airport.getLatitude();//1
            longitude_min=node.second.airport.getLongitude();//1
        }
    }
    return code;
}

std::list<std::string> Graph::findAirports(double latitude, double longitude){
    std::list<std::string> airports ;
    for (auto node: nodes) {//n
        if (utils::haversine(latitude,node.second.airport.getLatitude(),longitude,node.second.airport.getLongitude())<100) {//log(n)
            airports.push_back(node.first);//1
        }
    }
    return airports;
}

std::list<std::string> Graph::findAirportByCity(const std::string &city) {
    std::list<std::string> airports;
    for (auto node:nodes) {//n
        if(node.second.airport.getCity() == city)
            airports.push_back(node.first);//1
    }
    return airports;
}

int Graph::getNumberOfFlights(const std::string &airport_code) const {
    return nodes.at(airport_code).adj.size();
}

std::set<std::string> Graph::getAirlinesFromAirport(const std::string &airport_code) const {
    std::set<std::string> airlines;
    for(auto &a: nodes.at(airport_code).adj)//n
        airlines.insert(a.airline);//log(n)

    return airlines;
}

std::list<Airport> Graph::getAirportsReached(const std::string &source_airport, int k) {
    bfs(source_airport);

    std::list<Airport> airports;
    for(const auto &n: nodes) {
        const Node &node = n.second;
        if(node.airport.getCode() == source_airport)
            continue;
        if(node.travel_from_src.front().size() - 1 <= k)
            airports.push_back(node.airport);
    }

    return airports;
}

std::set<std::string> Graph::getCitiesReached(const std::string &source_airport, int k) {
    bfs(source_airport);

    std::set<std::string> cities;
    for(const auto &n: nodes) {
        const Node &node = n.second;
        if(node.airport.getCode() == source_airport)
            continue;
        if(node.travel_from_src.front().size() - 1 <= k)
            cities.insert(node.airport.getCity());
    }

    return cities;
}

std::set<std::string> Graph::getCountriesReached(const std::string &source_airport, int k) {
    bfs(source_airport);

    std::set<std::string> countries;
    for(const auto &n: nodes) {
        const Node &node = n.second;
        if(node.airport.getCode() == source_airport)
            continue;
        if(node.travel_from_src.front().size() - 1 <= k)
            countries.insert(node.airport.getCountry());
    }

    return countries;
}

std::set<std::string> Graph::getArrivalAirports(const std::string &airport_code) const {
    std::set<std::string> airports;
    for(auto &a: nodes.at(airport_code).adj)//v
        airports.insert(a.dest);//log n

    return airports;
}

std::set<std::string> Graph::getArrivalCities(const std::string &airport_code) const {
    std::set<std::string> cities;
    for(const Edge &edge: nodes.at(airport_code).adj)//n
        cities.insert(nodes.at(edge.dest).airport.getCity());//log n

    return cities;
}

std::set<std::string> Graph::getArrivalCountries(const std::string &airport_code) const {
    std::set<std::string> countries;
    for(const Edge &edge: nodes.at(airport_code).adj)//n
        countries.insert(nodes.at(edge.dest).airport.getCountry());//log n

    return countries;
}

bool Graph::checkIfAirportExists(const std::string &airport_code) const {
    return nodes.find(airport_code) != nodes.end();
}

void Graph::addWantedAirline(const std::string &airline_code) {
    wanted_airlines.insert(airline_code);
}

bool Graph::removeWantedAirline(const std::string &airline_code) {
    if(wanted_airlines.find(airline_code) == wanted_airlines.end())
        return false;

    wanted_airlines.erase(airline_code);
    return true;
}

void Graph::clearWantedAirline() {
    wanted_airlines.clear();
}

std::unordered_set<std::string> Graph::getWantedAirlines() const {
    return wanted_airlines;
}

