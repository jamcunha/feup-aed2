#include "../include/Menu.h"

Menu::Menu(): manager(AirManager()) {}

void Menu::init() const {

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

void Menu::airportInfo() const {
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
    std::cout << "\n\n";
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
    std::cout << "| 3 - Destinations                                     |\n";
    std::cout << "| 4 - Destination Countries                            |\n";
    std::cout << "|                                                      |\n";
    std::cout << "| 0 - Return to Main Menu                              |\n";
    std::cout << "--------------------------------------------------------\n";

    char opt;
    while(true) {
        std::cout << "\nOption: ";
        std::cin >> opt;
        if(opt <= '4' && opt >= '0')
            break;
        std::cout << "Not a valid option, please choose another.\n";
    }

    switch(opt) {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        default:
            utils::clearScreen();
            return;
    }
}

