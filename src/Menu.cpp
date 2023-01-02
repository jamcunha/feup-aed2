#include "../include/Menu.h"

#include <sstream>

Menu::Menu(): manager(AirManager()) {}

void Menu::init() {

    while(true) {
        utils::clearScreen();
        std::cout << "--------------------------------------------------------\n";
        std::cout << "|           Welcome to the Airport Manager             |\n";
        std::cout << "|                                                      |\n";
        std::cout << "| 1 - Flight                                           |\n";
        std::cout << "| 2 - Get Information About An Airport                 |\n";
        std::cout << "|                                                      |\n";
        std::cout << "| 0 - Exit                                             |\n";
        std::cout << "--------------------------------------------------------\n";

        char opt;
        while(true) {
            std::cout << "\nOption: ";
            std::cin >> opt;
            if(opt <= '2' && opt >= '0')
                break;
            std::cout << "Not a valid option, please choose another.\n";
        }

        switch(opt) {
            case '1':
                inputAirports();
                break;
            case '2':
                airportInfo();
                break;
            default:
                utils::clearScreen();
                return;
        }
    }
}

void Menu::inputAirports() const {
    std::string source, target, tmp;
    Airport airport;
    char opt;

    utils::clearScreen();
    while(true) {
        std::cout << "Please enter source airport code: ";
        std::cin >> source;

        if(manager.checkIfAirportExists(source)) {
            airport = manager.getAirport(source);
            std::cout << '\n';

            std::cout << "--------------------------------------------------------\n";
            std::cout << "|                    Airport Info                      |\n";

            /* extract to a function to avoid code duplication */
            tmp = "| Code: " + airport.getCode();
            std::cout << tmp;
            for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";

            tmp = "| Name : " + airport.getName();
            std::cout << tmp;
            for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";

            tmp = "| City : " + airport.getCity();
            std::cout << tmp;
            for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";

            tmp = "| Country : " + airport.getCountry();
            std::cout << tmp;
            for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";
            std::cout << "--------------------------------------------------------\n";

            std::cout << "\nConfirm [y/n/e(xit)]: ";
            std::cin >> opt;
            if(opt == 'y')
                break;
            else if(opt == 'e')
                return;

            utils::clearScreen();
        } else {
            std::cout << "Airport doesn't exists\n\n";
        }
    }

    utils::clearScreen();
    while(true) {
        std::cout << "Please enter target airport code: ";
        std::cin >> target;

        if(manager.checkIfAirportExists(target)) {
            airport = manager.getAirport(target);
            std::cout << '\n';

            std::cout << "--------------------------------------------------------\n";
            std::cout << "|                    Airport Info                      |\n";

            /* extract to a function to avoid code duplication */
            tmp = "| Code: " + airport.getCode();
            std::cout << tmp;
            for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";

            tmp = "| Name : " + airport.getName();
            std::cout << tmp;
            for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";

            tmp = "| City : " + airport.getCity();
            std::cout << tmp;
            for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";

            tmp = "| Country : " + airport.getCountry();
            std::cout << tmp;
            for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";
            std::cout << "--------------------------------------------------------\n";

            std::cout << "\nConfirm [y/n/e(xit)]: ";
            std::cin >> opt;
            if(opt == 'y')
                break;
            else if(opt == 'e')
                return;

            utils::clearScreen();
        } else {
            std::cout << "Airport doesn't exists\n\n";
        }
    }
}

void Menu::airportInfo() {
    std::string airport_code;
    Airport airport;

    utils::clearScreen();
    while(true) {
        std::cout << "Please enter the airport code: ";
        std::cin >> airport_code;

        if(manager.checkIfAirportExists(airport_code)) {
            airport = manager.getAirport(airport_code);
            break;
        }
        else
            std::cout << "Airport doesn't exists\n\n";
    }

    utils::clearScreen();
    std::string tmp;

    std::cout << "--------------------------------------------------------\n";
    std::cout << "|                    Airport Info                      |\n";

    /* extract to a function to avoid code duplication */
    tmp = "| Code: " + airport.getCode();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    tmp = "| Name : " + airport.getName();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    tmp = "| City : " + airport.getCity();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    tmp = "| Country : " + airport.getCountry();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    std::cout << "|                                                      |\n";
    std::cout << "| 1 - Flighs                                           |\n";
    std::cout << "| 2 - Airlines                                         |\n";
    std::cout << "| 3 - Destination Cities                               |\n";
    std::cout << "| 4 - Destination Countries                            |\n";
    std::cout << "| 5 - Reachable in x flights                           |\n";
    std::cout << "|                                                      |\n";
    std::cout << "| 0 - Return to Main Menu                              |\n";
    std::cout << "--------------------------------------------------------\n";

    char opt;
    while(true) {
        std::cout << "\nOption: ";
        std::cin >> opt;
        if(opt <= '5' && opt >= '0')
            break;
        std::cout << "Not a valid option, please choose another.\n";
    }

    switch(opt) {
        case '1':
            flightsFromAirportInfo(airport_code);
            break;
        case '2':
            airlinesFromAirportInfo(airport_code);
            break;
        case '3':
            citiesFromAirportInfo(airport_code);
            break;
        case '4':
            countriesFromAirportInfo(airport_code);
            break;
        case '5':
            reachInFlights(airport_code);
            break;
        default:
            utils::clearScreen();
            return;
    }
}

void Menu::flightsFromAirportInfo(const std::string &airport_code) const {
    std::set<std::string> airports = manager.getArrivalAirport(airport_code);
    std::string tmp;
    std::stringstream ss;

    utils::clearScreen();
    std::cout << "--------------------------------------------------------\n";

    std::cout << "| List of Airports:                                    |\n";
    std::cout << "|                                                      |\n";
    for(const std::string &airport_code: airports) {
        tmp = "| Airport - " + manager.getAirport(airport_code).getCode() /* + " - " + manager.getAirport(airport_code).getName() */;
        std::cout << tmp;
        for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
        std::cout << "|\n";
    }

    std::cout << "|                                                      |\n";

    ss << "| You can reach " << airports.size() << " airports.";
    tmp = ss.str();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    std::cout << "--------------------------------------------------------\n";
    std::cout << "\nPress <Enter> to go to main menu...";

    /* wait for enter to be pressed */
    std::cin.ignore(); // ignore characters in buffer
    while(std::cin.get() != '\n')
        continue;
}

void Menu::airlinesFromAirportInfo(const std::string &airport_code) const {
    std::list<Airline> airlines = manager.getAirlinesFromAirport(airport_code);
    std::string tmp;
    std::stringstream ss;

    utils::clearScreen();
    std::cout << "--------------------------------------------------------\n";

    std::cout << "| List of Airlines:                                    |\n";
    std::cout << "|                                                      |\n";
    for(const Airline &airline: airlines) {
        tmp = "| Airline - " + airline.getCode() /* + " - " + airline.getName() */;
        std::cout << tmp;
        for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
        std::cout << "|\n";
    }

    std::cout << "|                                                      |\n";

    ss << "| Airport have " << airlines.size() << " airlines available.";
    tmp = ss.str();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    std::cout << "--------------------------------------------------------\n";
    std::cout << "\nPress <Enter> to go to main menu...";

    /* wait for enter to be pressed */
    std::cin.ignore(); // ignore characters in buffer
    while(std::cin.get() != '\n')
        continue;
}

void Menu::citiesFromAirportInfo(const std::string &airport_code) const {
    std::set<std::string> cities = manager.getArrivalCities(airport_code);
    std::string tmp;
    std::stringstream ss;

    utils::clearScreen();
    std::cout << "--------------------------------------------------------\n";

    std::cout << "| List of Cities:                                      |\n";
    std::cout << "|                                                      |\n";
    for(const std::string &city: cities) {
        tmp = "| " + city;
        std::cout << tmp;
        for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
        std::cout << "|\n";
    }

    std::cout << "|                                                      |\n";

    ss << "| You can reach " << cities.size() << " cities.";
    tmp = ss.str();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    std::cout << "--------------------------------------------------------\n";
    std::cout << "\nPress <Enter> to go to main menu...";

    /* wait for enter to be pressed */
    std::cin.ignore(); // ignore characters in buffer
    while(std::cin.get() != '\n')
        continue;
}

void Menu::countriesFromAirportInfo(const std::string &airport_code) const {
    std::set<std::string> countries = manager.getArrivalCountries(airport_code);
    std::string tmp;
    std::stringstream ss;

    utils::clearScreen();
    std::cout << "--------------------------------------------------------\n";

    std::cout << "| List of Countries:                                   |\n";
    std::cout << "|                                                      |\n";
    for(const std::string &country: countries) {
        tmp = "| " + country;
        std::cout << tmp;
        for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
        std::cout << "|\n";
    }

    std::cout << "|                                                      |\n";

    ss << "| You can reach " << countries.size() << " countries.";
    tmp = ss.str();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    std::cout << "--------------------------------------------------------\n";
    std::cout << "\nPress <Enter> to go to main menu...";

    /* wait for enter to be pressed */
    std::cin.ignore(); // ignore characters in buffer
    while(std::cin.get() != '\n')
        continue;
}

void Menu::reachInFlights(const std::string &airport_code) {
    utils::clearScreen();
    std::cout << "--------------------------------------------------------\n";
    std::cout << "|         What information you want to know?           |\n";
    std::cout << "|                                                      |\n";
    std::cout << "| 1 - Airports                                         |\n";
    std::cout << "| 2 - Cities                                           |\n";
    std::cout << "| 3 - Countries                                        |\n";
    std::cout << "|                                                      |\n";
    std::cout << "| 0 - Return to Main Menu                              |\n";
    std::cout << "--------------------------------------------------------\n";

    char opt;
    while(true) {
        std::cout << "\nOption: ";
        std::cin >> opt;
        if(opt <= '3' && opt >= '0')
            break;
        std::cout << "Not a valid option, please choose another.\n";
    }

    int nr_flights;
    std::cout << "Maximum number of flights wanted: ";
    std::cin >> nr_flights;

    switch(opt) {
        case '1':
            reachableAirportsInFlights(airport_code, nr_flights);
            break;
        case '2':
            break;
        case '3':
            break;
        default:
            utils::clearScreen();
            return;
    }
}

void Menu::reachableAirportsInFlights(const std::string &airport_code, int nr_flights) {
    std::list<Airport> airports = manager.getAirportsReached(airport_code, nr_flights);
    std::string tmp;
    std::stringstream ss;

    utils::clearScreen();
    std::cout << "--------------------------------------------------------\n";

    std::cout << "| List of Airports:                                    |\n";
    std::cout << "|                                                      |\n";
    for(const Airport &airport: airports) {
        tmp = "| Airport - " + airport.getCode() /* + " - " + airport.getName() */;
        std::cout << tmp;
        for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
        std::cout << "|\n";
    }
    std::cout << "|                                                      |\n";

    ss << "| You can reach " << airports.size() << " airports.";
    tmp = ss.str();
    std::cout << tmp;
    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
    std::cout << "|\n";

    std::cout << "--------------------------------------------------------\n";
    std::cout << "\nPress <Enter> to go to main menu...";

    /* wait for enter to be pressed */
    std::cin.ignore(); // ignore characters in buffer
    while(std::cin.get() != '\n')
        continue;
}

