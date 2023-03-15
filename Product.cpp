#include "Product.h"
#include <sstream>
std::string promptValidString(std::string prompt)
{
    bool validInput = false;
    std::string userInput = "";
    while (!validInput)
    {
        std::cout << std::endl
                  << prompt;
        std::getline(std::cin >> std::ws, userInput);
        if (userInput.length() > 0)
        {
            validInput = true;
        }
    }
    return userInput;
}

/**
 * @brief only accepts an int or q, if q returns -1
 *
 * @param prompt string to be displayed prompting user for input
 * @return int integer >= 0 or -1 for quit
 */
int promptValidInt(std::string prompt)
{
    bool validInput = false;
    std::string userInput = "";
    int val = -1;
    while (!validInput)
    {
        std::cout << std::endl
                  << prompt;
        std::getline(std::cin >> std::ws, userInput);
        if (userInput == "q")
        {
            return -1;
        }
        val = atoi(userInput.c_str());
        if (val > 0)
        {
            validInput = true;
        } else if(userInput == "0") {
            validInput = true;
        }
    }
    return val;
}

/**
 * @brief prompt for a valid float, meaning greater than zero or "q", if q returns -1
 *
 * @param prompt string used to prompt user
 * @return float value >= 0 or -1 if user entered q
 */
float promptValidFloat(std::string prompt)
{
    bool validInput = false;
    std::string userInput = "";
    float val = -1;
    while (!validInput)
    {
        std::cout << std::endl
                  << prompt;
        std::getline(std::cin >> std::ws, userInput);
        if (userInput == "q")
        {
            return -1;
        }
        val = atof(userInput.c_str());
        if (val > 0)
        {
            validInput = true;
        }
    }
    return val;
}

double promptValidDouble(std::string prompt)
{
    bool validInput = false;
    std::string userInput = "";
    double val = -1;
    while (!validInput)
    {
        std::cout << std::endl
                  << prompt;
        std::getline(std::cin >> std::ws, userInput);
        val = std::stoi(userInput.c_str());
        if (val >= 0.00)
        {
            validInput = true;
        }
    }
    return val;
}

// retrieved from: https://www.techiedelight.com/determine-if-a-string-is-numeric-in-cpp/
bool isNumeric(std::string const &str)
{
    auto it = str.begin();
    while (it != str.end() && std::isdigit(*it))
    {
        it++;
    }
    return !str.empty() && it == str.end();
}

// retrieved from: https://stackoverflow.com/questions/447206/c-isfloat-function
bool isFloat(std::string myString)
{
    std::istringstream iss(myString);
    float f;
    iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

// -----Product-----

/**
 * @brief basic setter function to set the active status of a product
 *
 * @param active desired active state
 */
void Product::SetActive(bool active)
{
    this->active_ = active;
}

/**
 Converts the product to a string
*/
std::string Product::Stringify()
{
    std::stringstream stream;
    // type, buyer, seller, final price
    std::string returnVal;

    if (this->get_buyer() == NULL)
    {
        stream << "Product type: " << this->get_type_string() << ", Seller: " << this->get_seller()->get_name() << ", Current highest bid: " << this->get_last_bid();
        returnVal = stream.str();
    }
    else
    {
        stream << "Product type: " << this->get_type_string() << ", Buyer: " + this->get_buyer()->get_name() << ", Seller: " << this->get_seller()->get_name() << ", Final bid: " << std::fixed << std::setprecision(2) << this->get_final_bid();
        returnVal = stream.str();
    }

    return returnVal;
}

void Product::MakeBid(double bid, User *user)
{
    this->bid_vals_.push_back(bid);
    this->bidders_.push_back(user);
}

bool Product::CloseBid()
{
    this->active_ = false;
    // go to index 1 because 0 is seller
    for (unsigned int i = this->bidders_.size() - 1; i >= 1; i--)
    {
        // check if bidder has sufficient balance
        if (this->bidders_.at(i)->get_balance() >= this->bid_vals_.at(i))
        {
            this->bidders_.at(i)->ChangeBalance(this->bid_vals_.at(i));
            this->seller_ptr_->ChangeBalance(this->bid_vals_.at(i));
            this->SetBuyer(bidders_.at(i));
            this->SetFinalBid(this->bid_vals_.at(i));
            return true;
        }
    }
    return false;
}

/**
 reopens bidding at starting value
*/
void Product::OpenBid()
{
    this->active_ = true;
    float startingBid = this->bid_vals_.at(0);
    this->bid_vals_.clear();
    this->bidders_.clear();
    this->bid_vals_.push_back(startingBid);
    this->bidders_.push_back(this->seller_ptr_);
}

/**
    Sets the sellers id to the id specified

    @param newId the new id
*/
void Product::SetSeller(User *seller)
{
    if (seller != nullptr)
    {
        this->seller_ptr_ = seller;
    }
}

/**
    Sets the buyer id to the specified one

    @param newId the new id
*/
void Product::SetBuyer(User *buyer)
{
    if (buyer != nullptr)
    {
        this->buyer_ptr_ = buyer;
    }
}

/**
 Gets that most recent bid made on the product

 @return a float of the value of the most recent bid
*/
float Product::get_last_bid()
{
    if (this->bid_vals_.size() > 0)
    {
        return this->bid_vals_.back();
    }
    else
    {
        return 0;
    }
}

/**
    When a seller closes a sale this sets the greatest value bid to the final bid that won

    @param radius The radius of the circle.
    @return The volume of the sphere.
*/
void Product::SetFinalBid(double bid)
{
    if (bid >= 0)
    {
        this->final_bid_ = bid;
    }
    else
    {
        this->final_bid_ = 0;
    }
}

void Product::SetTitle(std::string newTitle)
{
    title_ = newTitle;
}

bool Product::SetCondition(int current_condition)
{
    switch (current_condition)
    {
    case 1:
        current_condition_ = Condition::New;
        return true;
        break;
    case 2:
        current_condition_ = Condition::Used_VeryGood;
        return true;
        break;
    case 3:
        current_condition_ = Condition::Used_Good;
        return true;
        break;
    case 4:
        current_condition_ = Condition::Used_okay;
        return true;
        break;

    default:
        std::cout << "Invalid Entry. Please try again" << std::endl;
        return false;
        break;
    }
}

std::string Product::get_condition(bool asString)
{
    if (asString)
    {
        switch (current_condition_)
        {
        case Condition::New:
            return "New";
            break;
        case Condition::Used_VeryGood:
            return "Used Very Good";
            break;
        case Condition::Used_Good:
            return "Used Good";
            break;
        case Condition::Used_okay:
            return "Used Okay";
            break;
        default:
            break;
        }
    }
    else
    {
        switch (current_condition_)
        {
        case Condition::New:
            return "1";
            break;
        case Condition::Used_VeryGood:
            return "2";
            break;
        case Condition::Used_Good:
            return "3";
            break;
        case Condition::Used_okay:
            return "4";
            break;
        default:
            break;
        }
    }
}

void Product::StartBid(double bid)
{
    bid_vals_.push_back(bid);
    bidders_.push_back(get_seller());
}

/**
    Displays the product id, the seller and buyer and the final price

    @param os the stream
    @param p the product to display the information of
    @return the stream to display the information to the user

std::ostream &operator<<(std::ostream &os, const Product &p)
{
    os << "ID: " << p.Stringify(p.get_type()) << ", seller -> buyer: " << p.seller_ptr_->get_name() << " -> " << p.buyer_ptr_->get_name() << ", final price: " << p.get_final_bid();
    return os;
}
*/

// -----Car-----
void Car::AssembleProduct()
{
    std::cout << "=========================================" << std::endl;
    this->SetTitle(promptValidString("Enter the listing title: "));
    this->SetMake(promptValidString("Enter make of car: "));
    this->SetModel(promptValidString("Enter model of car: "));
    this->SetYear(promptValidInt("Enter year of car: "));
    bool valid = false;
    while (!valid)
    {
        valid = this->SetCondition(promptValidInt("Enter the condition of your Car (1 - New , 2 - Used Very Good, 3 - Used Good, 4 - Used Okay): "));
    }
    this->StartBid(promptValidDouble("Starting Bid? "));
    std::cout << "=========================================" << std::endl;
}

void Car::AssignMetaData(std::string title, std::string make, std::string model, std::string year, std::string blank, std::string condition)
{
    this->SetTitle(title);
    this->SetMake(make);
    this->SetModel(model);
    this->SetYear(std::stoi(year));
    this->SetCondition(std::stoi(condition));
}

std::string Car::Stringify()
{
    std::stringstream stream;
    // type, buyer, seller, final price
    std::string returnVal;

    if (this->get_buyer() == NULL)
    {
        stream << "Product type: " << this->get_type_string() << ", Seller: " << this->get_seller()->get_name() << ", Current highest bid: " << std::fixed << std::setprecision(2) << bid_vals_.back() << std::endl
               << "Product description: " << this->get_title() << std::endl
               << "Make: " << this->GetMake() << std::endl
               << "Model: " << this->GetModel() << std::endl
               << "Year: " << this->GetYear() << std::endl
               << "Condition: " << this->get_condition(true);
        returnVal = stream.str();
        std::cout << "=========================================" << std::endl;
    }
    else
    {

        stream << "Product type: " << this->get_type_string() << ", Seller: " << this->get_seller()->get_name() << ", Buyer: " << this->get_buyer()->get_name() << ", Final bid: " << std::fixed << std::setprecision(2) << this->get_final_bid() << std::endl
               << "Product description: " << this->get_title() << std::endl
               << "Make: " << this->GetMake() << std::endl
               << "Model: " << this->GetModel() << std::endl
               << "Year: " << this->GetYear() << std::endl
               << "Condition: " << this->get_condition(true);
        returnVal = stream.str();
        std::cout << "=========================================" << std::endl;
    }

    return returnVal;
}

/**
    Sets the make of the car product

    @param newMake the make of the car to set to
*/
void Car::SetMake(std::string newMake)
{
    if (newMake.length() > 0)
    {
        this->make_ = newMake;
    }
}

/**
    Sets the model of the car

    @param newModel the model of the car to set to
*/
void Car::SetModel(std::string newModel)
{
    if (newModel.length() > 0)
    {
        this->model_ = newModel;
    }
}

/**
    Sets the year of the car

    @param newYear the year of the car to set to
*/
void Car::SetYear(unsigned int newYear)
{
    this->year_ = newYear;
}

std::string Car::get_metadata(int option)
{
    if (option == 1)
    {
        return GetMake();
    }
    else if (option == 2)
    {
        return GetModel();
    }
    else if (option == 3)
    {
        return std::to_string(GetYear());
    }
    return "";
}

// -----Furniture-----
void Furniture::AssembleProduct()
{
    std::cout << "=========================================" << std::endl;
    this->SetTitle(promptValidString("Enter the listing title: "));
    this->SetMaterial(promptValidString("What is the material? "));
    this->SetLength(promptValidFloat("What is the length of the product in inches? "));
    this->SetWidth(promptValidFloat("What is the width of the product in inches? "));
    this->SetHeight(promptValidFloat("What is the height of the product in inches? "));
    std::cout << "=========================================" << std::endl;

    bool valid = false;
    while (!valid)
    {
        valid = this->SetCondition(promptValidInt("Enter the condition of your Furniture (1 - New , 2 - Used Very Good, 3 - Used Good, 4 - Used Okay): "));
    }
    this->StartBid(promptValidDouble("Starting Bid? "));
}

void Furniture::AssignMetaData(std::string title, std::string material, std::string length, std::string width, std::string height, std::string condition)
{
    this->SetTitle(title);
    this->SetMaterial(material);
    this->SetLength(std::stof(length));
    this->SetWidth(std::stof(width));
    this->SetHeight(std::stof(height));
    this->SetCondition(std::stoi(condition));
};

std::string Furniture::Stringify()
{
    std::stringstream stream;
    // type, buyer, seller, final price
    std::string returnVal;

    if (this->get_buyer() == NULL)
    {
        stream << "Product type: " << this->get_type_string() << ", Seller: " << this->get_seller()->get_name() << ", Current highest bid: " << std::fixed << std::setprecision(2) << bid_vals_.back() << std::endl
               << "Product description: " << this->get_title() << std::endl
               << "Material: " << this->GetMaterial() << std::endl
               << "Length: " << this->GetLength() << "in" << std::endl
               << "Width: " << this->GetWidth() << "in" << std::endl
               << "Height: " << this->GetHeight() << "in" << std::endl
               << "Condition: " << this->get_condition(true);
        returnVal = stream.str();
        std::cout << "=========================================" << std::endl;
    }
    else
    {

        stream << "Product type: " << this->get_type_string() << ", Seller: " << this->get_seller()->get_name() << ", Buyer: " << this->get_buyer()->get_name() << ", Final bid: " << std::fixed << std::setprecision(2) << this->get_final_bid() << std::endl
               << "Product description: " << this->get_title() << std::endl
               << "Material: " << this->GetMaterial() << std::endl
               << "Length: " << this->GetLength() << "in" << std::endl
               << "Width: " << this->GetWidth() << "in" << std::endl
               << "Height: " << this->GetHeight() << "in" << std::endl
               << "Condition: " << this->get_condition(true);
        returnVal = stream.str();
        std::cout << "=========================================" << std::endl;
    }

    return returnVal;
}

/**
    Sets the material of the furniture product

    @param newMaterial the material of the furniture to set to
*/
void Furniture::SetMaterial(std::string newMaterial)
{
    if (newMaterial.length() > 0)
    {
        this->material_ = newMaterial;
    }
}

/**
    Sets the length dimension of the furniture product

    @param newLength the length to set to
*/
void Furniture::SetLength(float newLength)
{
    if (newLength < 0)
    {
        newLength = 0;
    }
    length_ = newLength;
}

/**
    Sets the width dimension of the furniture product

    @param newWidth the width to set to
*/
void Furniture::SetWidth(float newWidth)
{
    if (newWidth < 0)
    {
        newWidth = 0;
    }

    width_ = newWidth;
}

/**
    Sets the height dimension of the furniture product

    @param newHeight the height to set to
*/
void Furniture::SetHeight(float newHeight)
{
    if (newHeight < 0)
    {
        newHeight = 0;
    }
    height_ = newHeight;
}

std::string Furniture::get_metadata(int option)
{
    std::stringstream stream;
    if (option == 1)
    {
        return GetMaterial();
    }
    else if (option == 2)
    {
        stream << std::fixed << std::setprecision(2) << GetLength();
        
        return stream.str();
        
    }
    else if (option == 3)
    {
        stream << std::fixed << std::setprecision(2) << GetWidth();
        
        return stream.str();
    }
    else if (option == 4){
        stream << std::fixed << std::setprecision(2) << GetHeight();
        
        return stream.str();
    }
    return "";
}

// ------ Book -------
void Book::AssembleProduct()
{
    std::cout << "=========================================" << std::endl;
    this->SetTitle(promptValidString("Enter the listing title: "));
    this->SetBookTitle(promptValidString("What is the title of the book? "));
    this->SetAuthor(promptValidString("Who is the author? "));
    bool valid = false;
    while (!valid)
    {
        valid = this->SetCondition(promptValidInt("Enter the condition of your Book (1 - New , 2 - Used Very Good, 3 - Used Good, 4 - Used Okay): "));
    }
    this->StartBid(promptValidDouble("Starting Bid? "));
    std::cout << "=========================================" << std::endl;
}

void Book::AssignMetaData(std::string title, std::string book_title, std::string author, std::string blank, std::string blank2, std::string condition)
{
    this->SetTitle(title);
    this->SetBookTitle(book_title);
    this->SetAuthor(author);
    this->SetCondition(std::stoi(condition));
}

std::string Book::Stringify()
{
    std::stringstream stream;
    // type, buyer, seller, final price
    std::string returnVal;

    if (this->get_buyer() == NULL)
    {
        stream << "Product type: " << this->get_type_string() << ", Seller: " << this->get_seller()->get_name() << ", Current highest bid: " << std::fixed << std::setprecision(2) << bid_vals_.back() << std::endl
               << "Product description: " << this->get_title() << std::endl
               << "Book Title: " << this->GetBookTitle() << std::endl
               << "Author: " << this->GetAuthor() << std::endl
               << "Condition: " << this->get_condition(true);
        returnVal = stream.str();
        std::cout << "=========================================" << std::endl;
    }
    else
    {

        stream << "Product type: " << this->get_type_string() << ", Seller: " << this->get_seller()->get_name() << ", Buyer: " + this->get_buyer()->get_name() << ", Final bid: " << std::fixed << std::setprecision(2) << this->get_final_bid() << std::endl
               << "Product description: " << this->get_title() << std::endl
               << "Book Title: " << this->GetBookTitle() << std::endl
               << "Author: " << this->GetAuthor() << std::endl
               << "Condition: " << this->get_condition(true);
        returnVal = stream.str();
        std::cout << "=========================================" << std::endl;
    }

    return returnVal;
}

void Book::SetBookTitle(std::string newTitle)
{
    book_title_ = newTitle;
}

void Book::SetAuthor(std::string newAuthor)
{
    author_ = newAuthor;
}

std::string Book::get_metadata(int option)
{
    if (option == 1)
    {
        return GetBookTitle();
    }
    else if (option == 2)
    {
        return GetAuthor();
        
    }
    return "";
}

// --------- Computer -----------
void Computer::AssembleProduct()
{
    std::cout << "=========================================" << std::endl;
    this->SetTitle(promptValidString("Enter the listing title: "));
    this->SetScreenSize(promptValidFloat("What is the screen size? "));
    this->SetProcessorSpeed(promptValidFloat("What is the processor speed of the computer? "));
    this->SetMemory(promptValidFloat("What is the memory size? "));
    bool valid = false;
    while (!valid)
    {
        valid = this->SetCondition(promptValidInt("Enter the condition of your Computer (1 - New , 2 - Used Very Good, 3 - Used Good, 4 - Used Okay): "));
    }
    this->StartBid(promptValidDouble("Starting Bid? "));
    std::cout << "=========================================" << std::endl;
}

void Computer::AssignMetaData(std::string title, std::string screensize, std::string processorSpeed, std::string memory, std::string blank, std::string condition)
{
    this->SetTitle(title);
    this->SetScreenSize(std::stof(screensize));
    this->SetProcessorSpeed(std::stof(processorSpeed));
    this->SetMemory(std::stoi(memory));
    this->SetCondition(std::stoi(condition));
}

std::string Computer::Stringify()
{
    std::stringstream stream;
    // type, buyer, seller, final price
    std::string returnVal;

    if (this->get_buyer() == NULL)
    {
        stream << "Product type: " << this->get_type_string() << ", Seller: " << this->get_seller()->get_name() << ", Current highest bid: " << std::fixed << std::setprecision(2) << bid_vals_.back() << std::endl
               << "Product description: " << this->get_title() << std::endl
               << "Screen Size: " << this->GetScreenSize() << "in" << std::endl
               << "Processor Speed: " << this->GetProcessorSpeed() << "GHz" << std::endl
               << "Memory: " << this->GetMemory() << "GB" << std::endl
               << "Condition: " << this->get_condition(true);
        returnVal = stream.str();
        std::cout << "=========================================" << std::endl;
    }
    else
    {

        stream << "Product type: " << this->get_type_string() << ", Seller: " << this->get_seller()->get_name() << ", Buyer: " + this->get_buyer()->get_name() << ", Final bid: " << std::fixed << std::setprecision(2) << this->get_final_bid() << std::endl
               << "Product description: " << this->get_title() << std::endl
               << "Screen Size: " << this->GetScreenSize() << "in" << std::endl
               << "Processor Speed: " << this->GetProcessorSpeed() << "GHz" << std::endl
               << "Memory: " << this->GetMemory() << "GB" << std::endl
               << "Condition: " << this->get_condition(true);
        returnVal = stream.str();
        std::cout << "=========================================" << std::endl;
    }

    return returnVal;
}

void Computer::SetScreenSize(float newScreenSize)
{
    screenSize_ = newScreenSize;
}
void Computer::SetProcessorSpeed(float newSpeed)
{
    processorSpeed_ = newSpeed;
}
void Computer::SetMemory(unsigned int newMemory)
{
    memory_ = newMemory;
}

std::string Computer::get_metadata(int option)
{   std::stringstream stream;
    if (option == 1)
    {
        stream << std::fixed << std::setprecision(2) << GetScreenSize();
        
        return stream.str();
    }
    else if (option == 2)
    {
        stream << std::fixed << std::setprecision(2) << GetProcessorSpeed();
        
        return stream.str();
        
    }
    else if (option == 3)
    {
        stream << std::fixed << std::setprecision(2) << GetMemory();
        
        return stream.str();
    }
    return "";
}

//------------- Jewelry ---------
void Jewelry::AssembleProduct()
{
    std::cout << "=========================================" << std::endl;
    this->SetTitle(promptValidString("Enter the listing title: "));
    this->SetMaterial(promptValidString("What is the material (ex. silver or gold)? "));
    this->SetNumDiamonds(promptValidInt("How many jewels or diamonds? "));
    bool valid = false;
    while (!valid)
    {
        valid = this->SetCondition(promptValidInt("Enter the condition of your Jewelry (1 - New , 2 - Used Very Good, 3 - Used Good, 4 - Used Okay): "));
    }
    this->StartBid(promptValidDouble("Starting Bid? "));
    std::cout << "=========================================" << std::endl;
}

void Jewelry::AssignMetaData(std::string title, std::string material, std::string numDiamonds, std::string blank, std::string blank2, std::string condition)
{
    this->SetTitle(title);
    this->SetMaterial(material);
    this->SetNumDiamonds(std::stoi(numDiamonds));
    this->SetCondition(std::stoi(condition));
}

std::string Jewelry::Stringify()
{
    std::stringstream stream;
    // type, buyer, seller, final price
    std::string returnVal;

    if (this->get_buyer() == NULL)
    {
        stream << "Product type: " << this->get_type_string() << ", Seller: " << this->get_seller()->get_name() << ", Current highest bid: " << std::fixed << std::setprecision(2) << bid_vals_.back() << std::endl
               << "Product description: " << this->get_title() << std::endl
               << "Material: " << this->GetMaterial() << std::endl
               << "Number of jewels or diamonds: " << this->GetNumDiamonds() << std::endl
               << "Condition: " << this->get_condition(true);
        returnVal = stream.str();
        std::cout << "=========================================" << std::endl;
    }
    else
    {

        stream << "Product type: " << this->get_type_string() << ", Seller: " << this->get_seller()->get_name() << ", Buyer: " + this->get_buyer()->get_name() << ", Final bid: " << std::fixed << std::setprecision(2) << this->get_final_bid() << std::endl
               << "Product description: " << this->get_title() << std::endl
               << "Material: " << this->GetMaterial() << std::endl
               << "Number of jewels or diamonds: " << this->GetNumDiamonds() << std::endl
               << "Condition: " << this->get_condition(true);
        returnVal = stream.str();
        std::cout << "=========================================" << std::endl;
    }

    return returnVal;
}

void Jewelry::SetMaterial(std::string newMaterial)
{
    material_ = newMaterial;
}

void Jewelry::SetNumDiamonds(unsigned int newNumDiamonds)
{
    numDiamonds_ = newNumDiamonds;
}

std::string Jewelry::get_metadata(int option)
{
    std::stringstream stream;
    if (option == 1)
    {
        return GetMaterial();
    }
    else if (option == 2)
    {
        stream << std::fixed << std::setprecision(2) << GetNumDiamonds();
        
        return stream.str();
        
    }
    return "";
}