#ifndef FEUP_AED2_FLIGHT_H
#define FEUP_AED2_FLIGHT_H

#include "Airline.h"
#include "Airport.h"

class Flight {
private:
    Airport source_;
    Airport target_;
    Airline airline_;

public:
    Flight(Airport &source, Airport &target, Airline &airline);
};

#endif //FEUP_AED2_FLIGHT_H
