#ifndef FEUP_AED2_MENU_H
#define FEUP_AED2_MENU_H

#include "AirManager.h"
#include "Utils.h"

#include <iostream>
#include <string>

class Menu {
private:
    AirManager manager;

public:
    Menu();

    void init();

    void inputAirports() const;

    void airportInfo();

    void flightsFromAirportInfo(const std::string &airport_code) const;

    void airlinesFromAirportInfo(const std::string &airport_code) const;

    void citiesFromAirportInfo(const std::string &airport_code) const;

    void countriesFromAirportInfo(const std::string &airport_code) const;

    void reachInFlights(const std::string &airport_code);

    void reachableAirportsInFlights(const std::string &airport_code, int nr_flights);

    void reachableCitiesInFlights(const std::string &airport_code, int nr_flights);

    void reachableCountriesInFlights(const std::string &airport_code, int nr_flights);

    void settings();

    void input_city() const;

    void pages(std::list<std::list<std::pair<Airport, std::string>>> traveled_airports) const;

    void input_coordenates(int option) const;
};

#endif //FEUP_AED2_MENU_H
