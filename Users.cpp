#include <iostream>
#include <algorithm>
#include "Users.h"


/**
    Constructor for a user
*/
User::User(unsigned int id, std::string name, std::string phone, std::string address, double balance)
{
    this->userid_ = id;
    this->name_ = name;
    this->phone_ = phone;
    this->address_ = address;
    this->balance_ = balance;
}

/**
    Destructor for user
*/


/**
    Sets the name of the user
*/
void User::SetName(std::string newName)
{
    if (newName.length() > 0)
    {
        this->name_ = newName;
    }
}

/**
    Sets the phone number of the user
*/
void User::SetPhone(std::string newPhone)
{
    if (newPhone.length() > 0)
    {
        this->phone_ = newPhone;
    }
}

/**
    Sets the address of the user
*/
void User::SetAddress(std::string newAddress)
{
    if (newAddress.length() > 0)
    {
        this->address_ = newAddress;
    }
}

/**
    Asks the user what information they want to change, checks for valid input and changes the user information
*/
void User::UpdateInformation()
{
    bool active = true;
    while (active) //menu of options
    {
        std::cout << "===========================================" << std::endl;
        std::cout << "What information would you like to change?" << std::endl
                  << "(n)ame" << std::endl
                  << "(p)hone" << std::endl
                  << "(a)ddress" << std::endl
                  << "Enter (q) to go back" << std::endl;
        std::cout << "===========================================" << std::endl;
        std::string info_to_change = "";
        std::cin >> info_to_change;
        std::transform(info_to_change.begin(), info_to_change.end(), info_to_change.begin(), ::toupper); // translate their choice to uppercase
        if (info_to_change == "N")                                                                       // if user chooses to change their name
        {
            bool change_name = true;
            while (change_name)
            {
                std::cout << "==================================================================================================" << std::endl;
                std::cout << "Current Name: " << get_name() << std::endl;
                std::cout << "What would you like to change it to? Enter (q) if you no longer want to change your information" << std::endl;
                std::cout << "==================================================================================================" << std::endl;
                std::string change_to;
                std::getline(std::cin >> std::ws, change_to);
                std::string custom_case = change_to;
                std::transform(change_to.begin(), change_to.end(), change_to.begin(), ::toupper); // translate their choice to uppercase
                if (change_to == "Q")
                {
                    change_name = false;
                }
                else
                {
                    SetName(custom_case);
                    std::cout << "=================================================" << std::endl;
                    std::cout << "Your name has been changed to: " << get_name() << std::endl;
                    change_name = false;
                }
            }
        }
        else if (info_to_change == "P") // if user chooses to change phone
        {
            bool change_phone = true;
            bool success = true;

            while (change_phone)
            {
                std::cout << "==================================================================================================" << std::endl;
                std::cout << "Current Phone Number: " << get_phone() << std::endl;
                std::cout << "What would you like to change it to? Enter (q) if you no longer want to change your information" << std::endl;
                std::cout << "==================================================================================================" << std::endl;
                std::string change_to;
                std::cin >> change_to;
                std::string custom_case = change_to;
                std::transform(change_to.begin(), change_to.end(), change_to.begin(), ::toupper); // translate their choice to uppercase
                if (change_to == "Q")
                {
                    change_phone = false;
                    success = false;
                }
                else
                {
                    if (change_to.length() == 12 || change_to.length() == 10)
                    {
                        for (long unsigned int i = 0; i < change_to.length(); i++)
                        {
                            if (change_to[i] == 48 || change_to[i] == 49 || change_to[i] == 50 || change_to[i] == 51 || change_to[i] == 52 || change_to[i] == 53 || change_to[i] == 54 || change_to[i] == 55 || change_to[i] == 56 || change_to[i] == 57 || change_to[i] == 45)
                            {
                                continue;
                            }
                            else
                            {
                                std::cout << "Invalid Entry. Please enter your number in either of the following formats. 1234567890 or 123-456-7890." << std::endl;
                                success = false;
                            }
                        }
                    }
                    else
                    {
                        std::cout << "Invalid Entry. Please enter your number in either of the following formats. 1234567890 or 123-456-7890." << std::endl;
                        success = false;
                    }
                }
                if (success)
                {
                    SetPhone(change_to);
                    std::cout << "=======================================================" << std::endl;
                    std::cout << "Your Phone Number has been changed to: " << get_phone() << std::endl;
                    change_phone = false;
                }
            }
        }
        else if (info_to_change == "A") // if the user chooses address to change
        {
            bool change_address = true;

            while (change_address)
            {
                std::cout << "==================================================================================================" << std::endl;
                std::cout << "Current Address: " << get_address() << std::endl;
                std::cout << "What would you like to change it to? Enter (q) if you no longer want to change your information" << std::endl;
                std::cout << "==================================================================================================" << std::endl;
                std::string change_to;
                std::getline(std::cin >> std::ws, change_to);
                std::string custom_case = change_to;
                std::transform(change_to.begin(), change_to.end(), change_to.begin(), ::toupper); // translate their choice to uppercase
                if (change_to == "Q")
                {
                    change_address = false;
                }
                else
                {
                    SetAddress(custom_case);
                    std::cout << "=========================================================================================" << std::endl;
                    std::cout << "Your address has been changed to: " << get_address() << std::endl;
                    change_address = false;
                }
            }
        }
        else if (info_to_change == "Q")
        {
            active = false;
        }
        else
        {
            std::cout << "Invalid Entry. Valid choices are (n), (p), (a) or (q)." << std::endl;
        }
    }
}

/**
    Prints out all user information

    @param os the stream
    @param u the user
*/
std::ostream &operator<<(std::ostream &os, const User &u)
{
    os << "Name: " << u.name_ << ", Balance: " << u.balance_ << ", Phone: " << u.phone_ << ", Address: " << u.address_;
    return os;
}

/**
    Adds the specified amount to the sellers balance

    @param amount the amount to add
*/
void Seller::ChangeBalance(double amount)
{
    balance_ += amount;
    std::cout << "New Balance: " << balance_ << std::endl;
}

/**
    Subtracts the specified amount from the buyers balance

    @param amount 
*/
void Buyer::ChangeBalance(double amount)
{
    balance_ -= amount;
    std::cout << "New Balance: " << balance_ << std::endl;
}



void Seller::PrintOptions() {
    std::cout << "==================================================================================================" << std::endl;
    std::cout << "1) Post product for sale" << std::endl;
    std::cout << "2) Messaging" << std::endl;
    std::cout << "3) Check account balance" << std::endl;
    std::cout << "4) Update your informaiton" << std::endl;
    std::cout << "5) Overview of sold products" << std::endl;
    std::cout << "6) Manage bids" << std::endl;
    std::cout << "7) Sign out" << std::endl;
    std::cout <<  "==================================================================================================";
}

void Buyer::PrintOptions() {
    std::cout << "==================================================================================================" << std::endl;
    std::cout << "1) View products for sale" << std::endl;
    std::cout << "2) Messaging" << std::endl;
    std::cout << "3) Check account balance" << std::endl;
    std::cout << "4) Update your informaiton" << std::endl;
    std::cout << "5) Overview of placed bids" << std::endl;
    std::cout << "6) Manage bids" << std::endl;
    std::cout << "7) Sign out" << std::endl;
    std::cout <<  "==================================================================================================";
}

bool User::operator==(const User &other){
    return this->name_ == other.name_ && this->phone_ == other.phone_ && this->address_ == other.address_ && this->userid_ == other.userid_ && this->balance_ == other.balance_;
}