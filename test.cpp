#include "Driver.h"
#include <iostream>

int main() {
    std::cout << "BidToBuy Test" << std::endl;
    Driver * mainDriver = Driver::GetInstance();
    mainDriver->DisplayUsers();
}