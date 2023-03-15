#include "Driver.h"

/**
 * @brief Converts a string to a ProductCategory to aid in reading from CSVs
 *
 * @param type string that should be the same as one of the ProductCategory enums
 * @return ProductCategory Matched product category
 */
ProductCategory StringToProductCategory(std::string type)
{
    if (type == "Car")
    {
        return ProductCategory::Car;
    }
    else if (type == "Furniture")
    {
        return ProductCategory::Furniture;
    }
    else if (type == "Book")
    {
        return ProductCategory::Book;
    }
    else if (type == "Computer")
    {
        return ProductCategory::Computer;
    }
    else if (type == "Jewelry")
    {
        return ProductCategory::Jewelry;
    }
}

// retrieved from: https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
bool is_number(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

Driver *Driver::DriverPtr = NULL;

/**
 * @brief Construct a new Driver:: Driver object and read in form the CSV files
 *
 */
Driver::Driver()
{
    std::string line; // string to store each line

    std::ifstream fs("./runtime_data/user.csv"); // open file
    std::getline(fs, line);                      // get the header out of the way
    std::string name;
    std::string phone;
    std::string address;
    std::string bal;

    while (std::getline(fs, line))
    {                                      // read each line
        std::stringstream rowStream(line); // create a stringstream from the line
        // std::getline(rowStream, id, ',');
        std::getline(rowStream, name, ',');
        std::getline(rowStream, phone, ',');
        std::getline(rowStream, address, ',');
        std::getline(rowStream, bal);

        // User* tempUser = new User(stoi(id), (std::string)name, (std::string)phone, (std::string)address, stof(bal));
        User* tempUser = new User((std::string)name, (std::string)phone, (std::string)address, std::stod(bal));
        // User tempUser((std::string)id, (std::string)name, (std::string)phone, (std::string)address, stof(bal));
        this->users_.push_back(tempUser);
    }
    fs.close();
    fs.open("./runtime_data/products.csv");
    std::getline(fs, line); // get the header out of the way

    std::string type;
    std::string s_name;
    std::string b_name;
    std::string finalBid;
    std::string title;
    std::string meta_data1;
    std::string meta_data2;
    std::string meta_data3;
    std::string meta_data4;
    std::string condition;
    while (std::getline(fs, line))
    { // read each line
        // std::cout << line << std::endl;     // debugging
        std::stringstream rowStream(line);
        std::getline(rowStream, type, ',');
        std::getline(rowStream, s_name, ',');
        std::getline(rowStream, b_name, ',');
        std::getline(rowStream, finalBid, ',');
        std::getline(rowStream, title, ',');
        std::getline(rowStream, meta_data1, ',');
        std::getline(rowStream, meta_data2, ',');
        std::getline(rowStream, meta_data3, ',');
        std::getline(rowStream, meta_data4, ',');
        std::getline(rowStream, condition, ',');

        User *tempSellerPtr = nullptr;
        for (unsigned int i = 0; i < this->users_.size(); i++)
        {
            if (this->users_[i]->get_name() == s_name)
            {
                tempSellerPtr = this->users_[i];
                break;
            }
        }

        User *tempBuyerPtr = nullptr;
        for (unsigned int i = 0; i < this->users_.size(); i++)
        {
            if (this->users_[i]->get_name() == b_name)
            {
                tempBuyerPtr = this->users_[i];
                break;
            }
        }

        Product *tempProduct = ProductFactory::productFactory(StringToProductCategory(type), tempSellerPtr, false);
        tempProduct->SetBuyer(tempBuyerPtr);
        tempProduct->SetFinalBid(stof(finalBid));
        switch (StringToProductCategory(type))
        {
        case ProductCategory::Car:
            tempProduct->AssignMetaData(title, meta_data1, meta_data2, meta_data3, meta_data4, condition);
            break;
        case ProductCategory::Furniture:
            tempProduct->AssignMetaData(title, meta_data1, meta_data2, meta_data3, meta_data4, condition);
            break;
        case ProductCategory::Book:
            tempProduct->AssignMetaData(title, meta_data1, meta_data2, meta_data3, meta_data4, condition);
            break;
        case ProductCategory::Computer:
            tempProduct->AssignMetaData(title, meta_data1, meta_data2, meta_data3, meta_data4, condition);
            break;
        case ProductCategory::Jewelry:
            tempProduct->AssignMetaData(title, meta_data1, meta_data2, meta_data3, meta_data4, condition);
            break;
        default:
            break;
        }
        tempProduct->SetActive(false);
        this->sold_products_.push_back(tempProduct);
    }

    fs.close();
}

/**
 * @brief displays all users
 *
 */
void Driver::DisplayUsers()
{
    std::cout << "Number of users: " << this->users_.size() << std::endl;
    for (unsigned int i = 0; i < this->users_.size(); i++)
    {
        std::cout << i << ") " << *this->users_[i] << std::endl;
        // std::cout << i << std::endl;
    }
}

/**
 * @brief Displays sold products
 *
 * @param specific_to_user flag to set whether or not only products sold by a specified user are shown
 * @param Seller a pointer to a User object that is used if specific to user is true
 */
void Driver::DisplaySoldProducts(bool specific_to_user, User *Seller)
{
    if (specific_to_user)
    {
        std::vector<Product *> sellers_products;
        // iterate through sold products
        for (unsigned int i = 0; i < this->sold_products_.size(); i++)
        {
            // if seller of product is the same as the seller passed to this function
            if (this->sold_products_[i]->get_seller()->get_name() == Seller->get_name())
            {
                // add this product to the vector of found products
                sellers_products.push_back(this->sold_products_[i]);
            }
        }
        std::cout << "============================" << std::endl;
        std::cout << "Number of sold products: " << sellers_products.size() << std::endl;

        for (unsigned int i = 0; i < sellers_products.size(); i++)
        {
            std::cout << "=========================================================================" << std::endl;
            std::cout << i << ") " << sellers_products[i]->Stringify() << std::endl;
        }
    }
    else
    {
        std::cout << "============================" << std::endl;
        std::cout << "Number of sold products: " << this->sold_products_.size() << std::endl;

        for (unsigned int i = 0; i < this->sold_products_.size(); i++)
        {
            std::cout << "=========================================================================" << std::endl;
            std::cout << i << ") " << this->sold_products_[i]->Stringify() << std::endl;
        }
    }
}

/**
 * @brief Displays active products
 *
 * @param specific_to_user flag to set whether or not only products from a specified user are shown
 * @param seller Pointer to a User object to check check sold products for
 */
void Driver::DisplayActiveProducts(bool specific_to_user, User *seller)
{
    if (specific_to_user)
    {
        std::cout << "Products for sale by " << seller->get_name() << ":" << std::endl;
        std::vector<Product *> sellers_products;
        for (unsigned int i = 0; i < this->unsold_products_.size(); i++)
        {
            if (this->unsold_products_[i]->get_seller()->get_name() == seller->get_name() && this->unsold_products_[i]->get_active())
            {
                sellers_products.push_back(this->unsold_products_[i]);
            }
        }
        for (unsigned int i = 0; i < sellers_products.size(); i++)
        {
            std::cout << i << ") " << sellers_products[i]->Stringify() << std::endl;
        }
    }
    else
    {
        std::cout << "All products for sale: " << std::endl;
        for (unsigned int i = 0; i < this->unsold_products_.size(); i++)
        {
            std::cout << i << ") " << this->unsold_products_[i]->Stringify() << std::endl;
        }
    }
}

/**
 * @brief Displays inactive products from a seller meaning products that didn't succesfully sell
 *
 * @param seller pointer to User object to match products to
 */
void Driver::DisplayInactiveProducts(User *seller)
{
    std::cout << "Inactive products from " << seller->get_name() << ":" << std::endl;

    // collect inactive products
    std::vector<Product *> sellers_products;
    for (unsigned int i = 0; i < this->unsold_products_.size(); i++)
    {
        if (this->unsold_products_[i]->get_seller()->get_name() == seller->get_name() && !this->unsold_products_[i]->get_active())
        {
            sellers_products.push_back(this->unsold_products_[i]);
        }
    }

    // print out collect inactive products
    for (unsigned int i = 0; i < sellers_products.size(); i++)
    {
        std::cout << i << ") " << sellers_products[i]->Stringify() << std::endl;
    }
}

/**
 * @brief prints out all the bids that the given user has placed
 *
 * @param Buyer Pointer to a User object that will have it's bids displayed
 */
void Driver::DisplayCurrentBids(User *Buyer)
{
    std::cout << "Bids from " << Buyer->get_name() << ":" << std::endl;
    std::vector<Product *> current_bids;
    // std::cout << "unsold_products.size(): " << this->unsold_products_.size() << std::endl; //debugging
    for (unsigned int i = 0; i < this->unsold_products_.size(); i++)
    {
        // std::cout << "i: " << i << std::endl;   //debugging
        std::vector<User *> bids = this->unsold_products_[i]->get_bidders();
        for (unsigned int k = 0; k < bids.size(); k++)
        {
            // std::cout << "k: " << k << std::endl;   //debugging
            if (bids[k]->get_name() == Buyer->get_name())
            {
                // std::cout << "found bid" << std::endl;  //debugging
                current_bids.push_back(this->unsold_products_[i]);
            }
        }
    }
    for (unsigned int i = 0; i < current_bids.size(); i++)
    {
        std::cout << i << ") " << current_bids[i]->Stringify() << std::endl;
    }
}

/**
 * @brief creates a conversation between two users
 * 
 * @param buyer User pointer
 * @param seller User pointer
 */
void Driver::CreateConversation(User *buyer, User *seller)
{
    Conversation *convPtr = new Conversation(buyer, seller);
    this->conversations_.push_back(convPtr);
}

/**
 * @brief Handles the user interaction and logic for a user conversing
 *
 * @param userPtr a pointer to a User object that will be conversing
 */
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
        std::getline(std::cin >> std::ws, userInput);
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

/**
 * @brief checks whether or not a user with the given username exists
 *
 * @param name username to check if any user ahs
 * @return true A user with the given name exists
 * @return false A user with the give name does not exist
 */
bool Driver::UserExists(std::string name)
{
    for (unsigned int i = 0; i < users_.size(); i++)
    {
        if (users_[i]->get_name() == name)
        {
            return true;
        }
    }
    return false;
}

/**
 * Signs the user in with a username and has them select to be a buyer or a seller
 */
void Driver::signIn()
{
    std::string userName;
    bool validInput = false;
    while (!validInput)
    {
        std::cout << "=================" << std::endl;
        std::cout << "Enter your name: ";
        std::getline(std::cin >> std::ws, userName);
        if (userName.length() > 0 && UserExists(userName))
        {
            validInput = true;
        }
        else
        {
            std::cout << "User not found. Please try again!" << std::endl;
        }
    }
    validInput = false;
    std::string selection;
    while (!validInput)
    {
        std::cout << "================================" << std::endl;
        std::cout << "Do you wish to (b)uy or (s)ell?: ";
        std::getline(std::cin, selection);
        std::cout << "================================" << std::endl;
        if (selection == "b" || selection == "s")
        {
            validInput = true;
        }
        else
        {
            std::cout << "Invalid Entry. Please enter 'b' to buy or 's' to sell." << std::endl;
        }
    }
    for (unsigned int i = 0; i < this->users_.size(); i++)
    {
        if (this->users_[i]->get_name() == userName)
        {
            if (selection == "b")
            {
                // active_user_ = new Buyer(users_[i]->get_userid(), users_[i]->get_name(), users_[i]->get_phone(), users_[i]->get_address(), users_[i]->get_balance());
                active_user_ = new Buyer(users_[i]->get_name(), users_[i]->get_phone(), users_[i]->get_address(), users_[i]->get_balance());
            }
            else
            { // seller
                // active_user_ = new Seller(users_[i]->get_userid(), users_[i]->get_name(), users_[i]->get_phone(), users_[i]->get_address(), users_[i]->get_balance());
                active_user_ = new Seller(users_[i]->get_name(), users_[i]->get_phone(), users_[i]->get_address(), users_[i]->get_balance());
            }
        }
    }
}

/**
 * handles the the user interaction and logic for a seller to make a new listing for a product
 */
void Driver::HandleProductCreation()
{
    bool validInput = false;
    std::string userInput = "";
    int selection = 0;
    std::cout << "=========================================" << std::endl;
    std::cout << "What kind of product do you wish to sell?"
              << std::endl
              << "1) Car"
              << std::endl
              << "2) Furniture"
              << std::endl
              << "3) Book"
              << std::endl
              << "4) Computer"
              << std::endl
              << "5) Jewelry"
              << std::endl;
    std::cout << "=========================================" << std::endl;
    while (!validInput)
    {
        std::cout << std::endl
                  << "Enter number of desired type of product: ";
        std::getline(std::cin >> std::ws, userInput);
        selection = std::stoi(userInput);
        if (selection > 0 && selection < 6)
        {
            validInput = true;
        }
    }
    Product *new_product;
    switch (selection)
    {
    case 1: // car
    {
        new_product = ProductFactory::productFactory(ProductCategory::Car, active_user_, true);
    }
    break;
    case 2: // Furntiure
    {
        new_product = ProductFactory::productFactory(ProductCategory::Furniture, active_user_, true);
    }
    break;
    case 3: // Book
    {
        new_product = ProductFactory::productFactory(ProductCategory::Book, active_user_, true);
    }
    break;
    case 4: // Computer
    {
        new_product = ProductFactory::productFactory(ProductCategory::Computer, active_user_, true);
    }
    break;
    case 5: // Jewelry
    {
        new_product = ProductFactory::productFactory(ProductCategory::Jewelry, active_user_, true);
    }
    break;
    default:
        break;
    }
    new_product->SetActive(true);
    this->unsold_products_.push_back(new_product);
}

/**
 * Handles the user interaction and logic for a seller to view products for sale and place a bid on a product for sale
 */
void Driver::HandlePlaceBid()
{
    bool validInput = false;
    std::string input = "";
    int selection;
    while (!validInput)
    {
        this->DisplayActiveProducts(false, active_user_);
        std::cout << "Enter number of item to bid on or (q)uit: ";
        std::getline(std::cin >> std::ws, input);
        if (input == "q")
        {
            return;
        }
        else if (input.length() > 0 && isNumeric(input))
        {
            selection = stoi(input);
            if (selection >= 0 && selection < this->unsold_products_.size())
            {
                validInput = true;
                bool validInput2 = false;
                float bidAmount;
                while (!validInput2)
                {
                    bidAmount = promptValidFloat("Enter bid amount or (q)uit: ");
                    if (bidAmount >= 0)
                    {
                        // bidAmount = stof(input);
                        if (bidAmount > this->unsold_products_.at(selection)->get_last_bid())
                        {
                            validInput2 = true;
                            this->unsold_products_.at(selection)->MakeBid(bidAmount, this->active_user_);
                        }
                    }
                    else
                    { // user entered q
                        validInput2 = true;
                    }
                }
            }
        }
    }
}

/**
 * Handles the user interaction and logic behind a seller opening inactive or closing active bids
 */
void Driver::HandleOpenCloseBid()
{
    bool validInput = false;
    bool working = true; // flag for whether or not the user wants to continue working on bids
    std::string input = "";
    while (working)
    {
        validInput = false;
        // loops until the user inputs a valid option
        while(!validInput) {
            std::cout << std::endl << "View (a)ctive products, (i)nactive products or (q)uit: ";
            std::getline(std::cin >> std::ws, input);
            if (input == "q")
            {
                working = false;
                return;
            }
            else if (input == "a")
            {
                validInput = true;
            }
            else if (input == "i")
            {
                validInput = true;
            }
        }

        validInput = false; // reset flag to false
        int selection;
        if (input == "a") { // active products
           this->DisplayActiveProducts(true, this->active_user_);

           // collect the user's active products
           std::vector<Product*> activeProducts;
           for (unsigned int i = 0; i < this->unsold_products_.size(); i++)
            {
                if (this->unsold_products_[i]->get_seller()->get_name() == this->active_user_->get_name() && this->unsold_products_[i]->get_active())
                {
                    activeProducts.push_back(this->unsold_products_[i]);
                }
            }

            // loops until the user inputs a valid option
            while (!validInput) {
                selection = promptValidInt("Enter number of item to finalize sale of or (q)uit: ");
                if (selection >= 0 && (unsigned int)selection < activeProducts.size())
                {
                    validInput = true;
                }
                else if (selection == -1)
                {
                    validInput = true;
                }
            }

            // close the selected bid and move it to sold products vector if valid sale was made
            if(selection >= 0 && activeProducts.at(selection)->CloseBid()) {
                // check for conversation between the buyer and seller already existing
                bool foundConversation = false;
                for (unsigned int i = 0; i < this->conversations_.size(); i++)
                {
                    if(this->conversations_.at(i)->get_seller_ptr()->get_name() == this->active_user_->get_name() && this->conversations_.at(i)->get_buyer_ptr()->get_name() == activeProducts.at(selection)->get_buyer()->get_name()) {
                        foundConversation = true;
                        break;
                    }
                }

                // if conversation was not found create a new one
                if (!foundConversation)
                {
                    CreateConversation(activeProducts.at(selection)->get_buyer(), this->active_user_);
                }
                
                
                this->sold_products_.push_back(activeProducts.at(selection));
                for (unsigned int i = 0; i < this->unsold_products_.size(); i++)
                {
                    if (this->unsold_products_.at(i) == activeProducts.at(selection))
                    {
                        this->unsold_products_.erase(this->unsold_products_.begin() + i);
                        break;
                    }
                }
            }
        } else if (input == "i") {  // inactive products
            this->DisplayInactiveProducts(this->active_user_);

            // collect the user's inactive products
            std::vector<Product*> inactiveProducts;
            for (unsigned int i = 0; i < this->unsold_products_.size(); i++)
            {
                if (this->unsold_products_[i]->get_seller()->get_name() == this->active_user_->get_name() && !this->unsold_products_[i]->get_active())
                {
                    inactiveProducts.push_back(this->unsold_products_[i]);
                }
            }

            // loops until the user inputs a valid option
            while (!validInput) {
                selection = promptValidInt("Enter number of item to put back up for sale or (q)uit: ");
                if (selection >= 0 && selection < inactiveProducts.size())
                {
                    validInput = true;
                }
                else if (selection == -1)
                {
                    validInput = true;
                }
            }

            //if the selection is less than 0 that means that the user wants to quit
            if (selection >= 0) {
                inactiveProducts.at(selection)->OpenBid();
            }
        }
    }
}

/**
 * @brief handles the main looping function and menu functionality
 *
 */
void Driver::MainLoop()
{
    std::string userInput = ""; // stores the raw string input from the user
    int selection = 0;  // the integer value of the user's inputted selection
    bool signedIn = false;  // stores whether or not a user is signed in
    bool goodInput = false; // stores whether or not the inputted value was a valid option
    while (running_)
    {
        // check if a user is signed int
        if (!signedIn)
        {
            // if not then have the user sign in with a username
            this->signIn();
            signedIn = true;
        }
        active_user_->PrintOptions();   //print the options for the active user, this changes based on whether they are a seller or a buyer
        goodInput = false;  // reset goodInput to false
        if (active_user_->CheckUser())  // check whether the user is a buyer or a seller
        {                      // seller case
            // loops until the user inputs a valid option
            while (!goodInput) // get user input for main options
            {
                selection = promptValidInt("Enter number of desired action: ");
                if (selection > 0 && selection < 9)
                {
                    goodInput = true;
                }
            }
            switch (selection)
            {
            case 1: // post product
                this->HandleProductCreation();
                break;
            case 2: // messaging
                this->handleConversing(active_user_);
                break;
            case 3: // balance
                std::cout << "Your balance is: $" << active_user_->get_balance() << std::endl;
                break;
            case 4: // update info
                this->active_user_->UpdateInformation(this->get_users());
                break;
            case 5: // overview of products
                this->DisplaySoldProducts(true, this->active_user_);
                break;
            case 6: // manage bids
                this->HandleOpenCloseBid();
                break;
            case 7:
                this->active_user_ = nullptr;
                signedIn = false;
                break;
            case 8:
                this->running_ = false;
                UpdateUserCsv();
                UpdateProductsCsv();
                break;
            default:
                break;
            }
        }
        else
        {                      // buyer case
            // loops until the user inputs a valid option
            while (!goodInput) // get user input for main options
            {
                selection = promptValidInt("Enter number of desired action: ");
                if (selection > 0 && selection < 8)
                {
                    goodInput = true;
                }
            }
            switch (selection)
            {
            case 1: // view products for sale/place bid
                this->HandlePlaceBid();
                break;
            case 2: // messaging
                this->handleConversing(active_user_);
                break;
            case 3: // balance
                std::cout << "Your balance is: $" << active_user_->get_balance() << std::endl;
                break;
            case 4: // update info
                this->active_user_->UpdateInformation(this->get_users());
                break;
            case 5: // overview of placed bids
                this->DisplayCurrentBids(this->active_user_);
                break;
            case 6:
                this->active_user_ = nullptr;
                signedIn = false;
                break;
            case 7:
                this->running_ = false;
                break;
            default:
                break;
            }
        }
    }
}

/**
 * @brief prints out the sold products and products that are open for bidding for a given suer
 *
 * @param Seller
 */
void Driver::OverviewSeller(User *Seller)
{
    std::cout << "Sold Products: " << std::endl;
    DisplaySoldProducts(true, Seller);

    std::cout << "Products that are open for bidding: " << std::endl;
    DisplayActiveProducts(true, Seller);
}

/**
 * @brief prints out an overview of a user's bids
 *
 * @param Buyer
 */
void Driver::OverviewBuyer(User *Buyer)
{
    std::cout << "Products that you have placed a bid on: " << std::endl;
    DisplayCurrentBids(Buyer);
}

void Driver::UpdateUserCsv()
{
    std::ofstream outfs("./runtime_data/user.csv", std::ios::trunc);
    std::string name;
    std::string phone;
    std::string address;
    std::string bal;

    for (unsigned int k = 0; k < 2; k++)
    {
        if (k == 1)
        {
            for (unsigned int i = 0; i < users_.size(); i++)
            {
                name = users_[i]->get_name();
                phone = users_[i]->get_phone();
                address = users_[i]->get_address();
                bal = std::to_string(users_[i]->get_balance());

                outfs << name << "," << phone << "," << address << "," << bal << "\n";
            }
        }
        else
        {
            name = "name,";
            phone = "phone,";
            address = "address,";
            bal = "bal";
            outfs << name << phone << address << bal << "\n";
        }
    }
}

void Driver::UpdateProductsCsv()
{
    std::ofstream outfs("./runtime_data/products.csv", std::ios::trunc);
    std::string product_type;
    std::string seller;
    std::string buyer;
    std::string final_bid;
    std::string title;
    std::string meta_data1;
    std::string meta_data2;
    std::string meta_data3;
    std::string meta_data4;
    std::string condition;

    for (unsigned int k = 0; k < 2; k++)
    {
        if (k == 1)
        {
            for (unsigned int i = 0; i < sold_products_.size(); i++)
            {
                product_type = sold_products_[i]->get_type_string();
                seller = sold_products_[i]->get_seller()->get_name();
                buyer = sold_products_[i]->get_buyer()->get_name();
                final_bid = std::to_string(sold_products_[i]->get_final_bid());
                title = sold_products_[i]->get_title();
                meta_data1 = sold_products_[i]->get_metadata(1);
                meta_data2 = sold_products_[i]->get_metadata(2);
                meta_data3 = sold_products_[i]->get_metadata(3);
                meta_data4 = sold_products_[i]->get_metadata(4);
                condition = sold_products_[i]->get_condition(false);

                outfs << product_type << "," << seller << "," << buyer << "," << final_bid << "," << title << "," << meta_data1 << "," << meta_data2 << "," << meta_data3 << "," << meta_data4 << "," << condition << "\n";
            }
        }
        else
        {
            product_type = "product_type,";
            seller = "seller,";
            buyer = "buyer,";
            final_bid = "final_bid,";
            title = "title,";
            meta_data1 = "meta_data1,";
            meta_data2 = "meta_data2,";
            meta_data3 = "meta_data3,";
            meta_data4 = "meta_data4,";
            condition = "condition";
            outfs << product_type << seller << buyer << final_bid << title << meta_data1 << meta_data2 << meta_data3 << meta_data4 << condition << "\n";
        }
    }
}

