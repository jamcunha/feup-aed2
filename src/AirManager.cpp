#include "../include/AirManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

AirManager::AirManager() {
    this->airports_ = new Graph(true);
    this->how_to_fly = true;
    readData();
}

AirManager::~AirManager() {
    delete airports_;
}

Airport AirManager::getAirport(const std::string &airport_code) const {
    return airports_->getAirport(airport_code);
}

Airline AirManager::getAirline(const std::string &airline_code) const {
    return airlines_.at(airline_code);
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

// double AirManager::getDistance(const std::string &source_airport, const std::string &target_airport) {
//     return airports_->getShortestPath(source_airport, target_airport);
// }

std::list<std::list<std::pair<Airport,std::string>>> AirManager::getTraveledAirports(const std::string &source_airport, const std::string &target_airport) const {
    if (how_to_fly)
        return airports_->getTraveledAirports(source_airport, target_airport);
    return airports_->getTraveledAirportsByDistance(source_airport,target_airport);
}

std::list<std::list<std::pair<Airport,std::string>>>  AirManager::localCoordinates(double start_latitude, double start_longitude, double end_latitude, double end_longitude) const{
    std::list<std::list<std::pair<Airport,std::string>>> traveled,temp;
    std::list<std::string> start_airtports = airports_->findAirports(start_latitude,start_longitude);
    std::list<std::string> end_airports = airports_->findAirports(end_latitude,end_longitude);
    if (how_to_fly){
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

        return traveled;}
    bool flag = true;
    int distance=INF;
    for (auto i : start_airtports){
        for (auto j : end_airports){
            temp = airports_->getTraveledAirportsByDistance(i,j);
            if (airports_->getShortestPath(temp.front().front().first.getCode(),temp.front().back().first.getCode()) < distance || flag) {
                traveled=temp;
                distance=airports_->getShortestPath(temp.front().front().first.getCode(),temp.front().back().first.getCode());
                flag=false;
            }
            else if (airports_->getShortestPath(temp.front().front().first.getCode(),temp.front().back().first.getCode()) == distance)
                traveled.insert(traveled.end(),temp.begin(),temp.end());
        }
    }
    return traveled;
}

std::list<std::list<std::pair<Airport,std::string>>> AirManager::localCity(const std::string &start, const std::string &end) const {
    std::list<std::list<std::pair<Airport,std::string>>> traveled, temp;
    std::list<std::string> start_airtports = airports_->findAirportByCity(start);
    std::list<std::string> end_airports = airports_->findAirportByCity(end);
    if (how_to_fly){
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

        return traveled;}
    bool flag = true;
    int distance=INF;
    for (auto i : start_airtports){
        for (auto j : end_airports){
            temp = airports_->getTraveledAirportsByDistance(i,j);
            if (airports_->getShortestPath(temp.front().front().first.getCode(),temp.front().back().first.getCode()) < distance || flag) {
                traveled=temp;
                distance=airports_->getShortestPath(temp.front().front().first.getCode(),temp.front().back().first.getCode());
                flag=false;
            }
            else if (airports_->getShortestPath(temp.front().front().first.getCode(),temp.front().back().first.getCode()) == distance)
                traveled.insert(traveled.end(),temp.begin(),temp.end());
        }
    }
    return traveled;
}

std::list<std::list<std::pair<Airport,std::string>>>  AirManager::localCoordinatesClosest(double start_latitude, double start_longitude, double end_latitude, double end_longitude) const {
    std::string start = airports_->findAirport(start_latitude,start_longitude);
    std::string end = airports_->findAirport(end_latitude,end_longitude);
    if (how_to_fly)
        return airports_->getTraveledAirports(start,end);
    return airports_->getTraveledAirportsByDistance(start,end);
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

std::list<Airport> AirManager::getAirportsReached(const std::string &source_airport, int k) {
    return airports_->getAirportsReached(source_airport, k);
}

std::set<std::string> AirManager::getCitiesReached(const std::string &source_airport, int k) {
    return airports_->getCitiesReached(source_airport, k);
}

std::set<std::string> AirManager::getCountriesReached(const std::string &source_airport, int k) {
    return airports_->getCountriesReached(source_airport, k);
}

std::set<std::string> AirManager::getArrivalAirport(const std::string &airport_code) const {
    return airports_->getArrivalAirports(airport_code);
}

std::set<std::string> AirManager::getArrivalCities(const std::string &airport_code) const {
    return airports_->getArrivalCities(airport_code);
}

std::set<std::string> AirManager::getArrivalCountries(const std::string &airport_code) const {
    return airports_->getArrivalCountries(airport_code);
}

bool AirManager::checkIfAirportExists(const std::string &airport_code) const {
    return airports_->checkIfAirportExists(airport_code);
}

std::list<std::string> AirManager::findAirportByCity(const std::string &city) const{
    return airports_->findAirportByCity(city);
}

bool AirManager::checkIfAirlineExists(const std::string &airline_code) const {
    return (airlines_.find(airline_code) != airlines_.end());
}

bool AirManager::addWantedAirline(const std::string &airline_code) {
    if(airlines_.find(airline_code) == airlines_.end())
        return false;

    if(airports_->getWantedAirlines().find(airline_code) != airports_->getWantedAirlines().end())
        return false;

    airports_->addWantedAirline(airline_code);
    return true;
}

bool AirManager::removeWantedAirline(const std::string &airline_code) {
    if(airlines_.find(airline_code) == airlines_.end())
        return false;

    return airports_->removeWantedAirline(airline_code);
}

void AirManager::clearWantedAirline() {
    airports_->clearWantedAirline();
}

std::unordered_set<std::string> AirManager::getWantedAirlines() const {
    return airports_->getWantedAirlines();
}

bool AirManager::getHowToFly() const {
    return how_to_fly;
}

void AirManager::changeHowToFly() {
    how_to_fly = !how_to_fly;
}

