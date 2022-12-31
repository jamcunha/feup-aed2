#include <iostream>
#include "../include/AirManager.h"
#include "../include/Utils.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    AirManager airManager = AirManager();
    airManager.local_coordenates();
    return 0;
}
