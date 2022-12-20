#include "../include/Flight.h"

Flight::Flight(Airport &source, Airport &target, Airline &airline):
    source_(source), target_(target), airline_(airline) {}

