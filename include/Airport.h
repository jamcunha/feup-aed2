#ifndef FEUP_AED2_AIRPORT_H
#define FEUP_AED2_AIRPORT_H

#include <string>

class Airport {
private:
    /**
     *
     */
    std::string code_;
    /**
     *
     */
    std::string name_;
    /**
     *
     */
    std::string city_;
    /**
     *
     */
    std::string country_;
    /**
     *
     */
    double latitude_;
    /**
     *
     */
    double longitude_;

public:
    /**
     *
     */
    Airport() {};
    /**
     *
     * @param code
     * @param name
     * @param city
     * @param country
     * @param latitude
     * @param longitude
     */
    Airport(
        std::string code,
        std::string name,
        std::string city,
        std::string country,
        double latitude,
        double longitude
    );

    /**
     * @return
     */
    std::string getCity() const;
    std::string getCode() const;
    /**
     * @return
     */
    std::string getName() const;
    /**
     * @return
     */
    std::string getCountry() const;
    /**
     * @return
     */
    double getLatitude() const;
    /**
     * @return
     */
    double getLongitude() const;
    /**
     *
     * @param airport
     * @return
     */
    bool operator==(const Airport &airport) const;
};

#endif //FEUP_AED2_AIRPORT_H

