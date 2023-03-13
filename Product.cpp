#include "Product.h"
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
        val = atoi(userInput.c_str());
        if (val > 0)
        {
            validInput = true;
        }
    }
    return val;
}

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
        val = atof(userInput.c_str());
        if (val > 0)
        {
            validInput = true;
        }
    }
    return val;
}

// -----Product-----
std::string Product::Stringify()
{
    // type, buyer, seller, final price
    std::string returnVal;

    if (this->get_buyer() == NULL)
    {
        returnVal = "Product type: " + this->get_type_string() + ", Seller: " + this->get_seller()->get_name();
    }
    else
    {
        returnVal = "Product type: " + this->get_type_string() + ", Buyer: " + this->get_buyer()->get_name() + ", Seller: " + this->get_seller()->get_name() + ", Final bid: " + std::to_string(this->get_final_bid());
    }

    return returnVal;
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
 void Product::SetBuyer(User* buyer)
 {
     if (buyer != nullptr)
     {
         this->buyer_ptr_ = buyer;
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
    this->SetMake(promptValidString("Enter make of car: "));
    this->SetModel(promptValidString("Enter model of car: "));
    this->SetYear(promptValidInt("Enter year of car: "));
}

void Car::AssignMetaData(std::string make, std::string model, std::string year, std::string blank)
{

    this->SetMake(make);
    this->SetModel(model);
    this->SetYear(std::stoi(year));
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

// -----Furniture-----
void Furniture::AssembleProduct()
{
    std::cout << "Furniture made" << std::endl;
}

void Furniture::AssignMetaData(std::string material, std::string length, std::string width, std::string height)
{
    this->SetMaterial(material);
    this->SetLength(std::stof(length));
    this->SetWidth(std::stof(width));
    this->SetHeight(std::stof(height));
};

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

// ------ Book -------
void Book::AssembleProduct()
{
    std::cout << "Book made" << std::endl;
}

void Book::AssignMetaData(std::string title, std::string author, std::string blank1, std::string blank2)
{
    this->SetTitle(title);
    this->SetAuthor(author);
}
void Book::SetTitle(std::string newTitle)
{
    title_ = newTitle;
}

void Book::SetAuthor(std::string newAuthor)
{
    author_ = newAuthor;
}

// --------- Computer -----------
void Computer::AssembleProduct()
{
    std::cout << "Computer made" << std::endl;
}

void Computer::AssignMetaData(std::string screenSize, std::string processorSpeed, std::string memory, std::string blank)
{
    this->SetScreenSize(std::stof(screenSize));
    this->SetProcessorSpeed(std::stof(processorSpeed));
    this->SetMemory(std::stoi(memory));
}
void Computer::SetScreenSize(float newScreenSize){
    screenSize_ = newScreenSize;
}
void Computer::SetProcessorSpeed(float newSpeed){
    processorSpeed_ = newSpeed;
}
void Computer::SetMemory(unsigned int newMemory){
    memory_ = newMemory;
}


//------------- Jewelry ---------
void Jewelry::AssembleProduct()
{
    std::cout << "Jewelry made" << std::endl;
}

void Jewelry::AssignMetaData(std::string material, std::string numDiamonds, std::string blank1, std::string blank2)
{
    this->SetMaterial(material);
    this->SetNumDiamonds(std::stoi(numDiamonds));
}

void Jewelry::SetMaterial(std::string newMaterial){
    material_ = newMaterial;
}

void Jewelry::SetNumDiamonds(unsigned int newNumDiamonds){
    numDiamonds_ = newNumDiamonds;

}