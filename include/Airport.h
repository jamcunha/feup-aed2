#ifndef FEUP_AED2_AIRPORT_H
#define FEUP_AED2_AIRPORT_H

#include "City.h"
#include <string>

class Airport {
private:
    std::string code_;
    std::string name_;
    City city_;
    
    double latitude_;
    double longitude_;

public:
    Airport(
        std::string code,
        std::string name,
        City &city,
        double latitude,
        double longitude
    );
};

#endif //FEUP_AED2_AIRPORT_H
