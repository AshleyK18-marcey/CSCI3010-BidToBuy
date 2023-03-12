#include "Driver.h"
#include <iostream>

int main() {
    std::cout << "BidToBuy Test" << std::endl;
    Driver * mainDriver = Driver::GetInstance();
    mainDriver->DisplayUsers();
    mainDriver->DisplaySoldProducts();
    User* userPtr1 = new User(20, "name1", "111", "adr1", 0.0);
    User* userPtr2 = new User(20, "name2", "222", "adr2", 0.0);
    //mainDriver->DisplayUsers();
    mainDriver->CreateConversation(userPtr1, userPtr2);
    mainDriver->handleConversing(userPtr1);
    mainDriver->handleConversing(userPtr2);
}