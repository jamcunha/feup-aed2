#include <iostream>
#include "../include/AirManager.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    AirManager airManager = AirManager();
    airManager.local_city();
    return 0;
}
