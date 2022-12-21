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
    Flight(const Airport &source, const Airport &target, const Airline &airline);

    Airport getSource() const;
    Airport getTarget() const;
    Airline getAirline() const;
};

#endif //FEUP_AED2_FLIGHT_H
