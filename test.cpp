#include "Driver.h"
#include <iostream>

int main() {
    std::cout << "BidToBuy Test" << std::endl;
    Driver * mainDriver = Driver::GetInstance();
    mainDriver->DisplayUsers();
    User* userPtr1 = new User(20, "name1", "111", "adr1", 0.0);
    mainDriver->DisplaySoldProducts(false, userPtr1);
    User* userPtr2 = new User(20, "name2", "222", "adr2", 0.0);
    User* Ashley = new User(1, "Ashley", "111-111-1111", "central Park", 111);
    //mainDriver->DisplayUsers();
    //mainDriver->CreateConversation(userPtr1, userPtr2);
    //mainDriver->handleConversing(userPtr1);
    //mainDriver->handleConversing(userPtr2);
    mainDriver->OverviewSeller(Ashley);
}