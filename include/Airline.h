#ifndef FEUP_AED2_AIRLINE_H
#define FEUP_AED2_AIRLINE_H

#include <string>

class Airline {
private:
    std::string code_;
    std::string name_;
    std::string callsign_;
    std::string country_;

public:
    Airline(std::string code, std::string name, std::string callsign, std::string country);
};

#endif //FEUP_AED2_AIRLINE_H
