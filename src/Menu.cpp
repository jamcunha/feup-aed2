#include "../include/Menu.h"

Menu::Menu(): manager(AirManager()) {}

void Menu::init() const {

    while(true) {
        utils::clearScreen();

        std::cout << "--------------------------------------------------------\n";
        std::cout << "|           Welcome to the Airport Manager             |\n";
        std::cout << "|                                                      |\n";
        std::cout << "| 1 - Flight                                           |\n";
        std::cout << "|                                                      |\n";
        std::cout << "|                                                      |\n";
        std::cout << "|                                                      |\n";
        std::cout << "|                                                      |\n";
        std::cout << "| 0 - Exit                                             |\n";
        std::cout << "--------------------------------------------------------\n";

        char opt;
        while(true) {
            std::cout << "\nOpcao: ";
            std::cin >> opt;
            if(opt <= '1' && opt >= '0')
                break;
            std::cout << "Opcao nao valida, escolha outra opcao.\n";
        }

        switch(opt) {
            case '1':
                inputAirports();
                break;
            default:
                utils::clearScreen();
                return;
        }
    }
}

void Menu::inputAirports() const {
    std::string source, target;
    char opt;

    utils::clearScreen();
    while(true) {
        std::cout << "Please enter source airport code: ";
        std::cin >> source;

        if(manager.checkIfAirportExists(source)) {
            std::cout << '\n';
            utils::printAirportInfo(manager.getAirport(source));
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
            std::cout << '\n';
            utils::printAirportInfo(manager.getAirport(source));
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

