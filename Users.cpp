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

void User::SetAddress(std::string newAddress) {
    if (newAddress.length() > 0)
    {
        this->address_ = newAddress;
    }
}

std::ostream& operator<<(std::ostream& os, const User &u) {
    os << "Name: " << u.name_ << ", Balance: " << u.balance_ << ", Phone: " << u.phone_ << ", Address: " << u.address_;
    return os;
}