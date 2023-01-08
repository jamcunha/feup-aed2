#ifndef FEUP_AED2_AIRLINE_H
#define FEUP_AED2_AIRLINE_H

#include <string>

/**
 * @brief Represents a Airline.
 */
class Airline {
private:
    /**
     * @brief Internal code associated with the airline.
     * @details Acronym with 3 letters.
     */
    std::string code_;
    /**
     * @brief Name of the Airline.
     */
    std::string name_;
    /**
     * @brief Call-sign of the Airline.
     * @details Nickname of the Airline, some airlines have the call-sign be the same as its name.
     */
    std::string callsign_;
    /**
     * @brief Country of origin, where the airline was funded.
     */
    std::string country_;

public:
    //"Constructers"
    /**
     * @brief Create a new Airline.
     * @details Constructor of the Airline class.
     */
    Airline() {};
    /**
     * @brief Overloading of the class constructor.
     * @param code Internal code(IBE,SWE,RYR,ect.)
     * @param name Name of the new Airline
     * @param callsign Call-sign of the new Airline.
     * @param country Country where the new Ailrine was funded.
     */
    Airline(std::string code, std::string name, std::string callsign, std::string country);
    //"Getter"
    /**
     * @return Internal code.
     */
    std::string getCode() const;
    /**
     * @return Name of the Airline.
     */
    std::string getName() const;
    /**
     * @return Call-sign of the Airline.
     */
    std::string getCallsign() const;
    /**
     * @return Country of origin, where the country was funded.
     */
    std::string getCountry() const;
    //"Operators"
    /**
     * Compares the equality between two Airlines.
     * @param airline Airline to be compared.
     * @return True- If both internal codes are the same.
     * @return False- If the internal codes are not equal.
     */
    bool operator==(const Airline &airline) const;
};

#endif //FEUP_AED2_AIRLINE_H
