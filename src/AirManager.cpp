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

        airlines_.insert({ code, Airline(code, name, callsign, country) });
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
/*
double AirManager::getDistance(const std::string &source_airport, const std::string &target_airport) {
    return airports_->getShortestPath(source_airport, target_airport);
}*/

std::list<std::list<std::pair<Airport,std::string>>> AirManager::getTraveledAirports(const std::string &source_airport, const std::string &target_airport) {
    return airports_->getTraveledAirports(source_airport, target_airport);


}

std::list<std::list<std::pair<Airport,std::string>>>  AirManager::localCoordinates(double start_longitude, double start_latitude, double end_longitude, double end_latitude){
    std::list<std::list<std::pair<Airport,std::string>>> traveled,temp;
    std::list<std::string> start_airtports = airports_->findAirports(start_latitude,start_longitude);
    std::list<std::string> end_airports = airports_->findAirports(end_latitude,end_longitude);
    bool flag = true;
    for (auto i : start_airtports){
        for (auto j : end_airports){
            temp = airports_->getTraveledAirports(i,j);
            if (temp.size()<=traveled.size() || flag) {
                traveled=temp;
                flag=false;
            }
        }
    }

    return traveled;
}

std::list<std::list<std::pair<Airport,std::string>>>  AirManager::localCity(std::string start, std::string end){
    std::list<std::list<std::pair<Airport,std::string>>> traveled, temp;
    std::list<std::string> start_airtports = airports_->findAirportByCity(start);
    std::list<std::string> end_airports = airports_->findAirportByCity(end);
    bool flag = true;
    for (auto i : start_airtports){
        for (auto j : end_airports){
            temp = airports_->getTraveledAirports(i,j);
            if (temp.front().size()<traveled.front().size() || flag) {
                traveled=temp;
                flag=false;
            }
            else if (temp.front().size()==traveled.front().size())
                traveled.insert(traveled.end(),temp.begin(),temp.end());
        }

    }
    return traveled;
}

std::list<std::list<std::pair<Airport,std::string>>>  AirManager::localCoordinatesClosest(double start_longitude, double start_latitude, double end_longitude, double end_latitude) {
    std::string start = airports_->findAirport(start_latitude,start_longitude);
    std::string end = airports_->findAirport(end_latitude,end_longitude);
    return airports_->getTraveledAirports(start,end);
}

int AirManager::getMinFlights(const std::string &source_airport, const std::string &target_airport) {
    return airports_->getMinFlights(source_airport, target_airport);
}

int AirManager::getNumberOfFlights(const std::string &airport_code) const {
    return airports_->getNumberOfFlights(airport_code);
}

std::list<Airline> AirManager::getAirlinesFromAirport(const std::string &airport_code) const {
    std::set<std::string> airlines_code = airports_->getAirlinesFromAirport(airport_code);
    std::list<Airline> airlines;

    for(const std::string &it : airlines_code)
        airlines.push_back(airlines_.find(it)->second);

    return airlines;
}

std::set<std::string> AirManager::getArrivalCities(const std::string &airport_code) const {
    return airports_->getArrivalCities(airport_code);
}

std::set<std::string> AirManager::getArrivalCountries(const std::string &airport_code) const {
    return airports_->getArrivalCountries(airport_code);
}
