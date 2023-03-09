#include "Driver.h"


Driver* Driver::DriverPtr = NULL;

Driver::Driver() {
    std::string line;   // string to store each line

    std::ifstream fs("./runtime_data/users.csv"); // open file
    std::getline(fs, line);  // get the header out of the way

    std::string id;
    std::string name;
    std::string phone;
    std::string address;
    std::string bal;

    while (std::getline(fs, line)) { // read each line
        std::stringstream rowStream(line); // create a stringstream from the line
        std::getline(rowStream, id, ',');
        std::getline(rowStream, name, ',');
        std::getline(rowStream, phone, ',');
        std::getline(rowStream, address, ',');
        std::getline(rowStream, bal, ',');

        User tempUser(stoi(id), (std::string)name, (std::string)phone, (std::string)address, stof(bal));
        // User tempUser((std::string)id, (std::string)name, (std::string)phone, (std::string)address, stof(bal));
        this->users_.push_back(tempUser);
    }
    fs.close();
    fs.open("./runtime_data/products.csv");
    std::getline(fs, line);  // get the header out of the way

    std::string s_id;
    std::string b_id;
    std::string finalBid;
    while (std::getline(fs, line)) {  // read each line
        // std::cout << line << std::endl;     // debugging
        std::stringstream rowStream(line);
        std::getline(rowStream, id, ',');
        std::getline(rowStream, s_id, ',');
        std::getline(rowStream, b_id, ',');
        std::getline(rowStream, finalBid, ',');

        Product* tempProduct = productFactory(static_cast<ProductCategory>(stoi(id)), stoi(s_id));
        tempProduct->SetBuyerId(stoi(b_id));
        tempProduct->SetFinalBid(stof(finalBid));
        this->sold_products_.push_back(tempProduct);
    }

    fs.close();
}

void Driver::DisplayUsers() {
    std::cout << "Number of users: " << this->users_.size() << std::endl;
    for (unsigned int i = 0; i < this->users_.size(); i++)
    {
        std::cout << i << ") " << this->users_.at(i) << std::endl;
        // std::cout << i << std::endl;
    }
}

void Driver::DisplaySoldProducts() {
    std::cout << "Number of sold products: " << this->sold_products_.size() << std::endl;
    for (unsigned int i = 0; i < this->sold_products_.size(); i++)
    {
        std::cout << i << ") " << *this->sold_products_.at(i) << std::endl;
    }
}