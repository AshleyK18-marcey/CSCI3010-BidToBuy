#include "Driver.h"

// retrieved from: https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
bool is_number(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

Driver *Driver::DriverPtr = NULL;

Driver::Driver()
{
    std::string line; // string to store each line

    std::ifstream fs("./runtime_data/users.csv"); // open file
    std::getline(fs, line);                       // get the header out of the way

    std::string id;
    std::string name;
    std::string phone;
    std::string address;
    std::string bal;

    while (std::getline(fs, line))
    {                                      // read each line
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
    std::getline(fs, line); // get the header out of the way

    std::string s_id;
    std::string b_id;
    std::string finalBid;
    while (std::getline(fs, line))
    { // read each line
        // std::cout << line << std::endl;     // debugging
        std::stringstream rowStream(line);
        std::getline(rowStream, id, ',');
        std::getline(rowStream, s_id, ',');
        std::getline(rowStream, b_id, ',');
        std::getline(rowStream, finalBid, ',');

        Product *tempProduct = productFactory(static_cast<ProductCategory>(stoi(id)), stoi(s_id));
        tempProduct->SetBuyerId(stoi(b_id));
        tempProduct->SetFinalBid(stof(finalBid));
        this->sold_products_.push_back(tempProduct);
    }

    fs.close();
}

void Driver::DisplayUsers()
{
    std::cout << "Number of users: " << this->users_.size() << std::endl;
    for (unsigned int i = 0; i < this->users_.size(); i++)
    {
        std::cout << i << ") " << this->users_.at(i) << std::endl;
        // std::cout << i << std::endl;
    }
}

void Driver::DisplaySoldProducts(bool specific_to_user, User *Seller)
{
    if (specific_to_user)
    {
        std::vector<Product *> sellers_products;
        for (unsigned int i = 0; i < this->sold_products_.size(); i++)
        {
            if (this->sold_products_[i]->get_seller() == Seller)
            {
                sellers_products.push_back(this->sold_products_[i]);
            }
        }
        std::cout << "Number of sold products: " << sellers_products.size() << std::endl;
        for (unsigned int i = 0; i < sellers_products.size(); i++)
        {
            std::cout << i << ") " << *sellers_products.at(i) << std::endl;
        }
    }
    else
    {
        std::cout << "Number of sold products: " << this->sold_products_.size() << std::endl;
        for (unsigned int i = 0; i < this->sold_products_.size(); i++)
        {
            std::cout << i << ") " << *this->sold_products_.at(i) << std::endl;
        }
    }
}

void Driver::DisplayActiveProducts(User *seller)
{
    std::vector<Product *> sellers_products;
    for (unsigned int i = 0; i < this->unsold_products_.size(); i++)
    {
        if (this->unsold_products_[i]->get_seller() == seller)
        {
            sellers_products.push_back(this->sold_products_[i]);
        }
    }

    for (unsigned int i = 0; i < sellers_products.size(); i++)
    {
        std::cout << i << ") " << *sellers_products.at(i) << std::endl;
    }
}

void Driver::DisplayCurrentBids(User* Buyer){
    std::vector<Product*> current_bids;
    for(unsigned int i = 0; i < this->unsold_products_.size(); i++){
        std::vector<User*> bids = this->unsold_products_[i]->get_bidders();
        for(int k = 0; k < bids.size(); k++){
            if(bids[i] == Buyer){
                current_bids.push_back(this->unsold_products_[i]);
            }
        }
    }
    for(unsigned int i = 0; i < current_bids.size(); i++){
         std::cout << i << ") " << *current_bids.at(i) << std::endl;
    }
}

void Driver::CreateConversation(User *buyer, User *seller)
{
    Conversation *convPtr = new Conversation(buyer, seller);
    this->conversations_.push_back(convPtr);
}

void Driver::handleConversing(User *userPtr)
{
    std::vector<Conversation *> validConversations; // stores conversation that this user is a part of
    for (unsigned int i = 0; i < this->conversations_.size(); i++)
    {
        if (this->conversations_.at(i)->UserPresent(userPtr))
        {
            validConversations.push_back(this->conversations_.at(i));
        }
    }

    // print conversations to enter
    std::cout << "===========================" << std::endl;
    std::cout << "Selection) Buyer, Seller" << std::endl;
    std::cout << "===========================" << std::endl;
    for (unsigned int i = 0; i < validConversations.size(); i++)
    {
        std::cout << i << ") " << validConversations.at(i)->get_buyer_ptr()->get_name() << ", " << validConversations.at(i)->get_seller_ptr()->get_name() << std::endl;
    }
    bool validInput = false;
    std::string userInput;
    Conversation *selectedConversation;

    // select desired conversation
    while (!validInput)
    {
        std::cout << "===========================================================================" << std::endl;
        std::cout << "Enter the selection number of the conversation you'd like to view or (q)uit" << std::endl;
        std::cout << "===========================================================================" << std::endl;
        std::getline(std::cin, userInput);
        if (userInput == "q")
        {
            return;
        }
        if (is_number(userInput) && stoi(userInput) >= 0 && (unsigned int)stoi(userInput) < validConversations.size())
        {
            validInput = true;
            selectedConversation = validConversations.at(stoi(userInput));
        }
        else
        {
            std::cout << "======================================================================================" << std::endl;
            std::cout << "Invalid Entry. Please enter the selection number of the conversation or (q) to go back" << std::endl;
            std::cout << "======================================================================================" << std::endl;
        }
    }

    bool conversing = true;
    while (conversing)
    {
        std::cout << "===============================" << std::endl;
        selectedConversation->DisplayMessages();
        validInput = false;
        while (!validInput)
        {
            std::cout << std::endl
                      << "(s)end message or (q)uit?: " << std::endl;
            std::cout << "=============================" << std::endl;
            std::getline(std::cin, userInput);
            if (userInput == "q" || userInput == "s")
            {
                validInput = true;
            }
            else
            {
                std::cout << "Please enter 's' to send message or 'q' to go back" << std::endl;
            }
        }
        if (userInput == "q")
        {
            break;
        }
        validInput = false;
        while (!validInput)
        {
            std::cout << std::endl
                      << "Message: ";
            std::getline(std::cin, userInput);
            if (userInput.length() > 0)
            {
                validInput = true;
            }
        }
        selectedConversation->SendMessage(userInput, userPtr);
    }
}

bool Driver::UserExists(std::string name)
{
    for (unsigned int i = 0; i < users_.size(); i++)
    {
        if (users_.at(i).get_name() == name)
        {
            return true;
        }
    }
    return false;
}

void Driver::signIn()
{
    std::string userName;
    bool validInput = false;
    while (!validInput)
    {
        std::cout << "=================" << std::endl;
        std::cout << std::endl
                  << "Enter your name: ";
        std::getline(std::cin, userName);
        std::cout << "=================" << std::endl;
        if (userName.length() > 0 && UserExists(userName))
        {
            validInput = true;
        }
    }
    validInput = false;
    std::string selection;
    while (!validInput)
    {
        std::cout << "================================" << std::endl;
        std::cout << std::endl
                  << "Do you wish to (b)uy or (s)ell?: ";
        std::getline(std::cin, selection);
        std::cout << "================================" << std::endl;
        if (selection == "b" || selection == "s")
        {
            validInput = true;
        }
    }
    for (unsigned int i = 0; i < this->users_.size(); i++)
    {
        if (this->users_.at(i).get_name() == userName)
        {
            if (selection == "b")
            {
                active_user_ = new Buyer(users_.at(i).get_userid(), users_.at(i).get_name(), users_.at(i).get_phone(), users_.at(i).get_address(), users_.at(i).get_balance());
            }
            else
            { // seller
                active_user_ = new Seller(users_.at(i).get_userid(), users_.at(i).get_name(), users_.at(i).get_phone(), users_.at(i).get_address(), users_.at(i).get_balance());
            }
        }
    }
}

void Driver::MainLoop()
{
    std::string userInput = "";
    int selection = 0;
    bool signedIn = false;
    bool goodInput = false;
    while (running_)
    {
        if (!signedIn)
        {
            this->signIn();
        }
        active_user_->PrintOptions();
        goodInput = false;
        if (active_user_->CheckUser())
        {                      // seller
            while (!goodInput) // get user input for main options
            {
                std::cout << std::endl
                          << "Enter number of desired action: ";
                std::cin >> userInput;
                selection = std::stoi(userInput);
                if (selection > 0 && selection < 7)
                {
                    goodInput = true;
                }
            }
            switch (selection)
            {
            case 1: // post product
                /* code */
                break;
            case 2: // messaging
                this->handleConversing(active_user_);
                break;
            case 3: // balance
                std::cout << "Your balance is: " << active_user_->get_balance() << "dollars" << std::endl;
                break;
            case 4: // update info
                break;
            case 5: // overview of products
                break;
            case 6: // manage bids
                break;
            default:
                break;
            }
        }
        else
        { // buyer
        }
    }
}

void Driver::OverviewSeller(User *Seller)
{
    std::cout << "Sold Products: " << std::endl;
    DisplaySoldProducts(true, Seller);

    std::cout << "Products that are open for bidding: " << std::endl;
    DisplayActiveProducts(Seller);
}

void Driver::OverviewBuyer(User* Buyer){
    std::cout << "Products that you have placed a bid on: " << std::endl;
    DisplayCurrentBids(Buyer);
}
