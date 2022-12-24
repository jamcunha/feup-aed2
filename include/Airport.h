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
    Airport(
        std::string code,
        std::string name,
        std::string city,
        std::string country,
        double latitude,
        double longitude
    );

    std::string getCode() const;

    double getLatitude() const;

    double getLongitude() const;
};

#endif //FEUP_AED2_AIRPORT_H
