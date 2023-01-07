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
        std::cout << "| 9 - Settings                                         |\n";
        std::cout << "| 0 - Exit                                             |\n";
        std::cout << "--------------------------------------------------------\n";

        char opt;
        while(true) {
            std::cout << "\nOption: ";
            std::cin >> opt;
            if(opt <= '2' && opt >= '0' || opt == '9')
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
            case '9':
                settings();
                break;
            default:
                utils::clearScreen();
                return;
        }
    }
}

void Menu::inputAirports() const {
    while(true) {
        utils::clearScreen();
        std::cout << "--------------------------------------------------------\n";
        std::cout << "|           How do you pretend to search?              |\n";
        std::cout << "|                                                      |\n";
        std::cout << "| 1 - City                                             |\n";
        std::cout << "| 2 - Coordenates                                      |\n";
        std::cout << "| 3 - Coordenates (closest airport)                    |\n";
        std::cout << "|                                                      |\n";
        std::cout << "| 0 - Exit                                             |\n";
        std::cout << "--------------------------------------------------------\n";

        char opt;
        while(true) {
            std::cout << "\nOption: ";
            std::cin >> opt;
            if(opt <= '3' && opt >= '0')
                break;
            std::cout << "Not a valid option, please choose another.\n";
        }

        switch(opt) {
            case '1':
                input_city();
                break;
            case '2':
                input_coordenates(2);
                break;
            case '3':
                input_coordenates(3);
                break;
            default:
                utils::clearScreen();
                return;
        }
    }
}




void Menu::input_city() const {
    std::string source, target;
    Airport airport;
    char opt;
    utils::clearScreen();
    while (true) {
        std::cout << "Please enter the source city: ";
        std::cin.ignore();
        getline(std::cin,source);
        std::cout << "You entered " << source;
        std::cout << "\nConfirm [y/n/e(xit)]: ";
        std::cin >> opt;
        if(opt == 'y')
            break;
        else if(opt == 'e')
            return;
        utils::clearScreen();
    }
    utils::clearScreen();
    while (true) {
        std::cout << "Please enter the target city: ";
        std::cin.ignore();
        getline(std::cin,target);
        std::cout << "You entered " << target;
        std::cout << "\nConfirm [y/n/e(xit)]: ";
        std::cin >> opt;
        if(opt == 'y')
            break;
        else if(opt == 'e')
            return;
        utils::clearScreen();
    }
    std::list<std::list<std::pair<Airport, std::string>>> traveled_airports = manager.localCity(source, target);
    pages(traveled_airports);
}

void Menu::input_coordenates(int option) const {
    int source_latitude, source_longitude, target_latitude, target_longitude;
    std::stringstream ss;
    Airport airport;
    std::list<std::string> source, target;
    char opt;
    utils::clearScreen();
    while (true) {
        std::cout << "Please enter the source latitude: ";
        std::cin >> source_latitude;
        std::cout << "Please enter the source longitude: ";
        std::cin >> source_longitude;
        std::cout << "You entered " << source_latitude << ", " << source_longitude;
        std::cout << "\nConfirm [y/n/e(xit)]: ";
        std::cin >> opt;
        if(opt == 'y')
            break;
        else if(opt == 'e')
            return;
        utils::clearScreen();
    }
    utils::clearScreen();
    while (true) {
        std::cout << "Please enter the target latitude: ";
        std::cin >> target_latitude;
        std::cout << "Please enter the target longitude: ";
        std::cin >> target_longitude;
        std::cout << "You entered " << target_latitude << ", " << target_longitude;
        std::cout << "\nConfirm [y/n/e(xit)]: ";
        std::cin >> opt;
        if(opt == 'y')
            break;
        else if(opt == 'e')
            return;
        utils::clearScreen();
    }
    std::list<std::list<std::pair<Airport, std::string>>> traveled_airports;
    if (option==2){
        traveled_airports = manager.localCoordinates(source_latitude,source_longitude,target_latitude,target_longitude);
    }
    else
        traveled_airports = manager.localCoordinatesClosest(source_latitude,source_longitude,target_latitude,target_longitude);
    pages(traveled_airports);
}

void Menu::pages(std::list<std::list<std::pair<Airport, std::string>>> traveled_airports) const {
    if (traveled_airports.empty()){
        std::cout<<"There is no way to travel!\n";
        utils::clearScreen();
        return;
    }
    int page = 1;
    std::string tmp;
    std::stringstream ss;
    auto path = traveled_airports.begin();
    while (true) {
        utils::clearScreen();

        std::cout << "--------------------------------------------------------\n";
        std::cout << "|                    Flight Info                       |\n";
        std::cout << "|                                                      |\n";

        for (const auto &traveled_airport: *path) {
            tmp = "| Airport - " + traveled_airport.first.getCode() /* + " - " + traveled_airport.getName() */;
            std::cout << tmp;
            for (int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
            std::cout << "|\n";
        }
        std::cout << "|                                                      |\n";

        ss.str("");
        ss << "| You traveled by " << path->size() << " airports.";
        tmp = ss.str();
        std::cout << tmp;
        for (int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
        std::cout << "|\n";
        std::cout << "|                                                      |\n";

        ss.str("");
        ss << "| Page " << page << "/" << traveled_airports.size();
        tmp = ss.str();
        std::cout << tmp;
        for (int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
        std::cout << "|\n";
        std::cout << "--------------------------------------------------------\n";

        std::cout << "\nPress n(ext)/p(rev)/e(xit): ";

        char opt;
        while (true) {
            std::cin >> opt;
            if (opt == 'n') {
                page++;
                if (page > traveled_airports.size()) {
                    page = 1;
                    path = traveled_airports.begin();
                } else
                    ++path;
                break;
            } else if (opt == 'p') {
                page--;
                if (page < 1) {
                    page = traveled_airports.size();
                    path = traveled_airports.end();
                    --path;
                } else
                    --path;
                break;
            } else if (opt == 'e') {
                return;
            }
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
            reachableCitiesInFlights(airport_code, nr_flights);
            break;
        case '3':
            reachableCountriesInFlights(airport_code, nr_flights);
            break;
        default:
            utils::clearScreen();
            return; }
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

void Menu::reachableCitiesInFlights(const std::string &airport_code, int nr_flights) {
    std::set<std::string> cities = manager.getCitiesReached(airport_code, nr_flights);
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

void Menu::reachableCountriesInFlights(const std::string &airport_code, int nr_flights) {
    std::set<std::string> countries = manager.getCountriesReached(airport_code, nr_flights);
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

void Menu::settings() {
    while(true) {
        utils::clearScreen();
        std::cout << "--------------------------------------------------------\n";
        std::cout << "|                      Settings                        |\n";
        std::cout << "|                                                      |\n";
        std::cout << "| 1 - Add wanted airline                               |\n";
        std::cout << "| 2 - Remove wanted airline                            |\n";
        std::cout << "| 3 - Clear wanted airlines                            |\n";
        std::cout << "| 4 - List wanted airlines                             |\n";
        std::cout << "|                                                      |\n";
        std::cout << "| 0 - Exit                                             |\n";
        std::cout << "--------------------------------------------------------\n";

        char opt;
        while(true) {
            std::cout << "\nOption: ";
            std::cin >> opt;
            if(opt <= '4' && opt >= '0')
                break;
            std::cout << "Not a valid option, please choose another.\n";
        }

        std::unordered_set<std::string> wanter_airlines = manager.getWantedAirlines();
        std::string tmp;
        std::string airline_code;
        Airline airline;
        switch(opt) {
            case '1':
                utils::clearScreen();
                std::cout << "Type the airline code: ";
                std::cin >> airline_code;

                if(manager.checkIfAirlineExists(airline_code)) {
                    airline = manager.getAirline(airline_code);
                    std::cout << '\n';

                    std::cout << "--------------------------------------------------------\n";
                    std::cout << "|                    Airline Info                      |\n";

                    /* extract to a function to avoid code duplication */
                    tmp = "| Code: " + airline.getCode();
                    std::cout << tmp;
                    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
                    std::cout << "|\n";

                    tmp = "| Name : " + airline.getName();
                    std::cout << tmp;
                    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
                    std::cout << "|\n";

                    tmp = "| Call Sign : " + airline.getCallsign();
                    std::cout << tmp;
                    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
                    std::cout << "|\n";

                    tmp = "| Country : " + airline.getCountry();
                    std::cout << tmp;
                    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
                    std::cout << "|\n";
                    std::cout << "--------------------------------------------------------\n";

                    std::cout << "\nConfirm [y/n]: ";
                    std::cin >> opt;
                    if(opt == 'n')
                        break;

                    if(manager.addWantedAirline(airline_code))
                        std::cout << "\nAdded airline " << airline_code << " to wanted airlines.\n";
                    else
                        std::cout << "\nAirline already in the list.\n";
                } else {
                    std::cout << "Airline doesn't exists\n\n";
                }

                std::cout << "\nPress <Enter> to go to settings...";

                /* wait for enter to be pressed */
                std::cin.ignore(); // ignore characters in buffer
                while(std::cin.get() != '\n')
                    continue;

                break;
            case '2':
                utils::clearScreen();
                std::cout << "Type the airline code: ";
                std::cin >> airline_code;

                if(manager.checkIfAirlineExists(airline_code)) {
                    airline = manager.getAirline(airline_code);
                    std::cout << '\n';

                    std::cout << "--------------------------------------------------------\n";
                    std::cout << "|                    Airline Info                      |\n";

                    /* extract to a function to avoid code duplication */
                    tmp = "| Code: " + airline.getCode();
                    std::cout << tmp;
                    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
                    std::cout << "|\n";

                    tmp = "| Name : " + airline.getName();
                    std::cout << tmp;
                    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
                    std::cout << "|\n";

                    tmp = "| Call Sign : " + airline.getCallsign();
                    std::cout << tmp;
                    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
                    std::cout << "|\n";

                    tmp = "| Country : " + airline.getCountry();
                    std::cout << tmp;
                    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
                    std::cout << "|\n";
                    std::cout << "--------------------------------------------------------\n";

                    std::cout << "\nConfirm [y/n]: ";
                    std::cin >> opt;
                    if(opt == 'n')
                        break;

                    if(manager.removeWantedAirline(airline_code))
                        std::cout << "\nRemoved airline " << airline_code << " from wanted airlines.\n";
                    else
                        std::cout << "\nAirline not found.\n";
                } else {
                    std::cout << "Airline doesn't exists\n\n";
                }

                std::cout << "\nPress <Enter> to go to settings...";

                /* wait for enter to be pressed */
                std::cin.ignore(); // ignore characters in buffer
                while(std::cin.get() != '\n')
                    continue;

                break;
            case '3':
                utils::clearScreen();
                manager.clearWantedAirline();

                std::cout << "Cleared wanted airlines.\n";

                std::cout << "\nPress <Enter> to go to main menu...";

                /* wait for enter to be pressed */
                std::cin.ignore(); // ignore characters in buffer
                while(std::cin.get() != '\n')
                    continue;

                return;
            case '4':
                utils::clearScreen();

                std::cout << "--------------------------------------------------------\n";
                std::cout << "| List of Wanted Airlines:                             |\n";
                std::cout << "|                                                      |\n";

                for(const std::string &airline_code: wanter_airlines) {
                    tmp = "| Airline - " + airline_code;
                    std::cout << tmp;
                    for(int i = 0; i < 55 - tmp.length(); i++) std::cout << " ";
                    std::cout << "|\n";
                }
                std::cout << "--------------------------------------------------------\n";

                std::cout << "\nPress <Enter> to go to main menu...";

                /* wait for enter to be pressed */
                std::cin.ignore(); // ignore characters in buffer
                while(std::cin.get() != '\n')
                    continue;

                break;
            default:
                utils::clearScreen();
                return;
        }
    }
}

