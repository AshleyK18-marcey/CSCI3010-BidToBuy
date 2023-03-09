#include <iostream>
#include <algorithm>
#include "Users.h"

User::User(unsigned int id, std::string name, std::string phone, std::string address, float balance) {
    this->userid_ = id;
    this->name_ = name;
    this->phone_ = phone;
    this->address_ = address;
    this->balance_ = balance;
}

void User::SetName(std::string newName) {
    if (newName.length() > 0)
    {
        this->name_ = newName;
    }
}

void User::SetPhone(std::string newPhone){
    if(newPhone.length() > 0){
        this->phone_ = newPhone;
    }
}

void User::SetAddress(std::string newAddress) {
    if (newAddress.length() > 0)
    {
        this->address_ = newAddress;
    }
}

void User::UpdateInformation()
{
    bool active = true;
    while (active)
    {
        std::cout << "===========================================" <<std::endl;
        std::cout << "What information would you like to change?" << std::endl
                  << "Name" << std::endl
                  << "Phone" << std::endl
                  << "Address" << std::endl
                  << "Enter cancel to go back" << std::endl;
        std::cout << "===========================================" <<std::endl;
        std::string info_to_change = "";
        std::cin >> info_to_change;
        std::cout << info_to_change << std::endl;
        std::transform(info_to_change.begin(), info_to_change.end(), info_to_change.begin(), ::toupper); // translate their choice to uppercase
        if (info_to_change == "NAME")
        {
            bool change_name = true;
            while (change_name)
            {
                std::cout << "==================================================================================================" <<std::endl;
                std::cout << "Current Name: " << get_name() << std::endl;
                std::cout << "What would you like to change it to? Enter Cancel if you no longer want to change your information" << std::endl;
                std::cout << "==================================================================================================" <<std::endl;
                std::string change_to;
                std::getline(std::cin >> std::ws, change_to);
                std::string custom_case = change_to;
                std::transform(change_to.begin(), change_to.end(), change_to.begin(), ::toupper); // translate their choice to uppercase
                if (change_to == "CANCEL")
                {
                    change_name = false;
                }
                else
                {
                    SetName(custom_case);
                    std::cout << "===========================================" <<std::endl;
                    std::cout << "Your name has been changed to: " << get_name() << std::endl;
                    change_name = false;
                }
                
            }
        }
        else if (info_to_change == "PHONE")
        {
            bool change_phone = true;
            bool success = true;
            while (change_phone)
            {
                std::cout << "==================================================================================================" <<std::endl;
                std::cout << "Current Phone Number: " << get_phone() << std::endl;
                std::cout << "What would you like to change it to? Enter Cancel if you no longer want to change your information" << std::endl;
                std::cout << "==================================================================================================" <<std::endl;
                std::string change_to;
                std::cin >> change_to;
                std::string custom_case = change_to;
                std::transform(change_to.begin(), change_to.end(), change_to.begin(), ::toupper); // translate their choice to uppercase
                if (change_to == "CANCEL")
                {
                    change_phone = false;
                    success = false;
                }
                else
                { 
                    if(change_to.length() == 12 || change_to.length() == 10){
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
                    else{
                        std::cout << "Invalid Entry. Please enter your number in either of the following formats. 1234567890 or 123-456-7890." << std::endl;
                        success = false;
                    }
                    
                }
                if (success)
                {   
                    SetPhone(change_to);
                    std::cout << "Your Phone Number has been changed to: " << get_phone() << std::endl;
                    change_phone = false;
                }
            }
        }
        else if (info_to_change == "ADDRESS")
        {
            bool change_address = true;
            while (change_address)
            {
                std::cout << "==================================================================================================" <<std::endl;
                std::cout << "Current Address: " << get_address() << std::endl;
                std::cout << "What would you like to change it to? Enter Cancel if you no longer want to change your information" << std::endl;
                std::cout << "==================================================================================================" <<std::endl;
                std::string change_to;
                std::getline(std::cin, change_to);
                std::string custom_case = change_to;
                std::cout << custom_case << std::endl;
                std::transform(change_to.begin(), change_to.end(), change_to.begin(), ::toupper); // translate their choice to uppercase
                if (change_to == "CANCEL")
                {
                    change_address = false;
                }
                else
                {
                     SetAddress(custom_case);
                     std::cout << "Your address has been changed to: " << get_address() << std::endl;
                     change_address = false;
                }
               
            }
        }
        else if (info_to_change == "CANCEL")
        {
            active = false;
        }
        else
        {
            std::cout << "That was not a valid entry. Please try again" << std::endl;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const User &u) {
    os << "Name: " << u.name_ << ", Balance: " << u.balance_ << ", Phone: " << u.phone_ << ", Address: " << u.address_;
    return os;
}