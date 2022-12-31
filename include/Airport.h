#ifndef FEUP_AED2_AIRPORT_H
#define FEUP_AED2_AIRPORT_H

#include <string>

class Airport {
private:
    std::string code_;
    std::string name_;
    std::string city_;
    std::string country_;
    
    double latitude_;
    double longitude_;

public:
    Airport() {};

    Airport(
        std::string code,
        std::string name,
        std::string city,
        std::string country,
        double latitude,
        double longitude
    );


    std::string getCity() const;
    std::string getCode() const;

    double getLatitude() const;

    double getLongitude() const;

    bool operator==(const Airport &airport) const;
};

#endif //FEUP_AED2_AIRPORT_H
