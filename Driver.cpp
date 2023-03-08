#include "Driver.h"


Driver* Driver::DriverPtr = NULL;

Driver::Driver() {
    std::ifstream fs("./runtime_data/users.csv"); // open file
    std::string line;   // string to store each line
    std::getline(fs, line);
    std::string id;
    std::string name;
    std::string phone;
    std::string address;
    std::string bal;
    while (std::getline(fs, line)) { // read each line
        // std::cout << line << std::endl;     //debugging
        std::stringstream rowStream(line); // create a stringstream from the line
        std::getline(rowStream, id, ',');
        std::getline(rowStream, name, ',');
        std::getline(rowStream, phone, ',');
        std::getline(rowStream, address, ',');
        std::getline(rowStream, bal, ',');

        User tempUser(stoi(id), (std::string)name, (std::string)phone, (std::string)address, stof(bal));
        // this->users_.push_back(tempUser);
    }
    fs.close();
    // fs.open("runtime_data/products.csv");
}

void Driver::DisplayUsers() {
    std::cout << "Number of users: " << this->users_.size() << std::endl;
    for (unsigned int i = 0; i < this->users_.size(); i++)
    {
        // std::cout << i << this->users_.at(i) << std::endl;
        std::cout << i << std::endl;
    }
}