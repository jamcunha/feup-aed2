#ifndef FEUP_AED2_CITY_H
#define FEUP_AED2_CITY_H

#include <string>

class City {
private:
    std::string city_;
    std::string country_;

public:
    City(std::string city, std::string country);

    std::string getCity() const;
    
    std::string getCoutry() const;
};

#endif //FEUP_AED2_CITY_H
