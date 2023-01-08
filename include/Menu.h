#ifndef FEUP_AED2_MENU_H
#define FEUP_AED2_MENU_H

#include "AirManager.h"
#include "Utils.h"

#include <iostream>
#include <string>

/**
 * Represents the menu.
 */
class Menu {
private:
    AirManager manager;

public:
    /**
     * @brief Constructor of the Menu class.
     * @details Also creates a new Manager to execute every action needed.
     */
    Menu();
    /**
     * @brief Initializes the main menu.
     */
    void init();
    /**
     * @brief Initializes the search flights menu.
     * @details This menu is used to select which search method will be used to explore the air traffic.
     */
    void inputFlights() const;
    /**
     * @brief Initializes the airport info menu.
     * @details This menu is used to give access to all information about a airport such as name,location,flights available,etc.
     */
    void airportInfo();
    /**
     * @brief Prints all airports reachable in all flights available in a single airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code
     */
    void flightsFromAirportInfo(const std::string &airport_code) const;
    /**
     * @brief Prints all airlines available in a single airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code
     */
    void airlinesFromAirportInfo(const std::string &airport_code) const;
    /**
     * @brief Prints all cities reachable within all of the flights available in a single airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code
     */
    void citiesFromAirportInfo(const std::string &airport_code) const;
    /**
     * @brief Prints all counties reachable within all of the flights available in a single airport.
     * @details Time Complexity- O(|E| log(|V|)).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code
     */
    void countriesFromAirportInfo(const std::string &airport_code) const;
    /**
     * @brief Opens the menu to help costumers view all places reachable within a wanted number of flights starting from a source airport.
     * @param airport_code Airport's code.
     */
    void reachInFlights(const std::string &airport_code);
    /**
     * @brief Prints all airports reachable within a fixed number of flights starting from a source airport.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @param nr_flights  Number of flights desired.
     */
    void reachableAirportsInFlights(const std::string &airport_code, int nr_flights);
    /**
     * @brief Prints all cities reachable within a fixed number of flights starting from a source airport.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @param nr_flights  Number of flights desired.
     */
    void reachableCitiesInFlights(const std::string &airport_code, int nr_flights);
    /**
     * @brief Prints all countries reachable within a fixed number of flights starting from a source airport.
     * @details Time Complexity - O(|V| + |E|).
     * @details V is the number of vertices/nodes and E is the number of edges/links.
     * @param airport_code Airport's code.
     * @param nr_flights  Number of flights desired.
     */
    void reachableCountriesInFlights(const std::string &airport_code, int nr_flights);
    /**
     * @brief Opens the settings menu.
     * @details This menu is used to set the favoured airlines desired by the client.
     */
    void settings();
    /**
     * @brief Opens the inputting menu for cities.
     * @details This menu is used to input the current city where the client is and the desired city the client wants to go.
     */
    void inputCity() const;
    /**
     * @brief Prints all the traveled airports in a trip the client selected.
     * @details In case of impossible travels this menu also warns the client.
     * @param traveled_airports List of all the airports traveled.
     */
    void pages(const std::list<std::list<std::pair<Airport, std::string>>> &traveled_airports) const;
    /**
     * @brief Opens the inputting menu for gps coordinates of the airports.
     * @details This menu is used to input the current airport's coordinates where the client is and the desired airport's coordinates the client wants to go.
     * @param option Option to input the exact coordinates or not.
     * @details option=true means the client wants to input the exact coordinates of a airport and option=false means the client will just input coordinates close to the airport.
     */
    void inputCoordinates(bool option) const;
    /**
     * @brief Opens the inputting menu for airports.
     * @details This menu is used to input the current airport where the client is and the desired airport the client wants to go.
     */
    void inputAirport() const;
};

#endif //FEUP_AED2_MENU_H
