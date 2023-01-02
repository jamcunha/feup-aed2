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

    void init() const;

    void inputAirports() const;

    void airportInfo() const;

    void flightsFromAirportInfo(const std::string &airport_code) const;

    void airlinesFromAirportInfo(const std::string &airport_code) const;
};

#endif //FEUP_AED2_MENU_H
