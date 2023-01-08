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
    Airline() {};
    Airline(std::string code, std::string name, std::string callsign, std::string country);

    std::string getCode() const;
    std::string getName() const;
    std::string getCallsign() const;
    std::string getCountry() const;

    bool operator==(const Airline &airline) const;
};

#endif //FEUP_AED2_AIRLINE_H
