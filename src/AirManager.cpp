#include "../include/AirManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

AirManager::AirManager() {
    this->airports_ = new Graph(true);
    readData();
}

AirManager::~AirManager() {
    delete airports_;
}

void AirManager::readData() {
    std::ifstream airlines_input("../data/airlines.csv");
    std::ifstream airports_input("../data/airports.csv");
    std::ifstream flights_input("../data/flights.csv");

    std::string line;

    /* discard first line */
    getline(airlines_input, line);
    getline(airports_input, line);
    getline(flights_input, line);

    /* store airlines */
    while(getline(airlines_input, line)) {
        std::stringstream ss(line);

        std::string code, name, callsign, country;

        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, callsign, ',');
        getline(ss, country, '\r');

        airlines_.insert(Airline(code, name, callsign, country));
    }

    /* add airports to graph */
    while(getline(airports_input, line)) {
        std::stringstream ss(line);
        
        std::string code, name, city, country, latitude_string, longitude_string;

        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, city, ',');
        getline(ss, country, ',');
        getline(ss, latitude_string, ',');
        getline(ss, longitude_string, '\r');

        double latitude = std::stod(latitude_string);
        double longitude = std::stod(longitude_string);

        cities_.insert(city);

        airports_->addNode(code, Airport(code, name, city, country, latitude, longitude));
    }

    /* add flights to airports */
    while(getline(flights_input, line)) {
        std::stringstream ss(line);

        std::string source, target, airline;

        getline(ss, source, ',');
        getline(ss, target, ',');
        getline(ss, airline, '\r');

        airports_->addEdge(source, target, airline);
    }
}

double AirManager::getDistance(const std::string &source_airport, const std::string &target_airport) {
    return airports_->getShortestPath(source_airport, target_airport);
}

std::list<Airport> AirManager::getTraveledAirports(const std::string &source_airport, const std::string &target_airport) {
    return airports_->getTraveledAirports(source_airport, target_airport);


}

void AirManager::local_coordenates(){
    double start_longitude, start_latitude, end_longitude, end_latitude;
    std::cout<<"Insert start's longitude: \n";
    std::cin >> start_longitude;
    std::cout<<"Insert start's latitude: \n";
    std::cin >> start_latitude;
    std::cout<<"Insert end's longitude: \n";
    std::cin >> end_longitude;
    std::cout<<"Insert end's latitude: \n";
    std::cin >> end_latitude;
    std::list<std::list<Airport>> traveled;
    std::list<std::string> start_airtports = airports_->findAirports(start_latitude,start_longitude);
    std::list<std::string> end_airports = airports_->findAirports(end_latitude,end_longitude);
    std::list<Airport> temp;
    bool flag = true;
    for (auto i : start_airtports){
        for (auto j : end_airports){
            temp = airports_->getTraveledAirports(i,j);
            if (temp.size()<=traveled.size() || flag) {
                traveled.push_back(temp);
                flag=false;
            }
        }
    }
    std::cout<<"Path:\n";
    for (auto i :traveled){
        for (auto j:i){
            std::cout<<"->"<<j.getCode();
        }
        std::cout<<"\n";
    }
}



void AirManager::local_city(){
    std::string start, end;
    std::cout<<"Insert start's city: \n";
    getline(std::cin, start);
    std::cout<<"Insert end's city: \n";
    getline(std::cin, end);
    std::list<std::list<Airport>> traveled;
    std::list<std::string> start_airtports = airports_->findAirport_city(start);
    std::list<std::string> end_airports = airports_->findAirport_city(end);
    std::list<Airport> temp;
    bool flag = true;
    for (auto i : start_airtports){
        for (auto j : end_airports){
            temp = airports_->getTraveledAirports(i,j);
            if (temp.size()<=traveled.size() || flag) {
                traveled.push_back(temp);
                flag=false;
            }
        }
    }
    std::cout<<"Path:\n";
    for (auto i :traveled){
        for (auto j:i){
            std::cout<<"->"<<j.getCode();
        }
        std::cout<<"\n";
    }
}

void AirManager::local_coordenates_closest() {
    double start_longitude, start_latitude, end_longitude, end_latitude;
    std::cout<<"Insert start's longitude: \n";
    std::cin >> start_longitude;
    std::cout<<"Insert start's latitude: \n";
    std::cin >> start_latitude;
    std::cout<<"Insert end's longitude: \n";
    std::cin >> end_longitude;
    std::cout<<"Insert end's latitude: \n";
    std::cin >> end_latitude;
    std::string start = airports_->findAirport(start_latitude,start_longitude);
    std::string end = airports_->findAirport(end_latitude,end_longitude);
    std::cout<<"Path:\n";
    for (auto i :airports_->getTraveledAirports(start, end)){
        std::cout<<"->"<<i.getCode();
    }
}
