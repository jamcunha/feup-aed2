#ifndef FEUP_AED2_AIRPORT_H
#define FEUP_AED2_AIRPORT_H

#include <string>
/**
 * @brief Represents a Airport.
 */
class Airport {
private:
    /**
     * @brief Internal code associated with the airport.
     * @details Acronym with 3 letters.
     */
    std::string code_;
    /**
     *@brief Name of the airport.
     */
    std::string name_;
    /**
     * @brief The city in which is located.
     */
    std::string city_;
    /**
     * @brief The country in which is located.
     */
    std::string country_;
    /**
     * @brief The latitude coordinates of the building.
     */
    double latitude_;
    /**
     * @brief The longitude coordinates of the building.
     */
    double longitude_;

public:
    //"Constructers"
    /**
     * @brief Creates a new Airport
     * @details Constructor of the Airport class.
     */
    Airport() {};
    /**
     * @brief Overloading of the constructor.
     * @param code Airport's Code.
     * @param name Airport's name.
     * @param city The host city.
     * @param country The host country.
     * @param latitude Latitude coordinates of the building.
     * @param longitude Longitude coordinates of the building.
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
     * @brief Gets the host city of the airport.
     * @return City's name.
     */
    std::string getCity() const;
    /**
     * @brief Gets the internal code of the airport.
     * @return Airport's code.
     */
    std::string getCode() const;
    /**
     * @brief Gets the name of the airport.
     * @return Airport's name.
     */
    std::string getName() const;
    /**
     * @brief Gets the host country of the airport.
     * @return Country's name.
     */
    std::string getCountry() const;
    /**
     * @brief Gets the latitude coordinates of the airport.
     * @return Latitude in degrees,
     */
    double getLatitude() const;
    /**
     * @brief Gets the longitude coordinates of the airport.
     * @return Longitude in degrees,
     */
    double getLongitude() const;
    /**
     * Compares the equality between two airports.
     * @param airport Airport to be compared.
     * @return True- If both internal codes are the same.
     * @return False- If the internal codes are not equal.
     */
    bool operator==(const Airport &airport) const;
};

#endif //FEUP_AED2_AIRPORT_H

