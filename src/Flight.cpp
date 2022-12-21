#include "../include/Flight.h"

Flight::Flight(const Airport &source, const Airport &target, const Airline &airline):
    source_(source), target_(target), airline_(airline) {}

Airport Flight::getSource() const {
    return source_;
}

Airport Flight::getTarget() const {
    return target_;
}

Airline Flight::getAirline() const {
    return airline_;
}

