#include "../include/AirManager.h"

#include <fstream>
#include <sstream>

AirManager::AirManager() {
    this->airports_ = new Graph(true);
    readData();
}

AirManager::~AirManager() {
    delete airports_;
}

Airport AirManager::getAirport(const std::string &airport_code) const {
    return airports_->getAirport(airport_code);
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

double AirManager::getDistance(const std::string &source_airport, const std::string &target_airport) {
    return airports_->getShortestPath(source_airport, target_airport);
}

int AirManager::getMinFlights(const std::string &source_airport, const std::string &target_airport) {
    return airports_->getMinFlights(source_airport, target_airport);
}

std::list<Airport> AirManager::getTraveledAirports(const std::string &source_airport, const std::string &target_airport) {
    return airports_->getTraveledAirports(source_airport, target_airport);
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
