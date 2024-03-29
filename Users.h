#ifndef USERS_H
#define USERS_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>


// #include "Product.h"

class User
{
public:
  // User(unsigned int id, std::string name, std::string phone, std::string address, double balance);
  User(std::string name, std::string phone, std::string address, double balance);
  //~User();
 // ~User();

  float get_balance() { return balance_; };

  // unsigned int get_userid() { return userid_; };

  std::string get_name() { return name_; };

  std::string get_phone() { return phone_; };

  std::string get_address() { return address_; };

  void SetName(std::string newName);

  void SetPhone(std::string newPhone);

  void SetAddress(std::string newAddress);

  void UpdateInformation(std::vector<User*> list_of_current_users);

  virtual void ChangeBalance(double amount) { std::cout << balance_ << std::endl; };

  // checks whether the user is a buyer or a seller
  virtual bool CheckUser() { return false; };

  virtual void PrintOptions() {};

  bool operator==(const User &other);

  friend std::ostream &operator<<(std::ostream &os, const User &u);

  

private:
  // unsigned int userid_;

protected:
  std::string title_;
  double balance_;
  std::string name_;
  std::string phone_;
  std::string address_;
};

class Seller : public User
{
public:
  // Seller(unsigned int id, std::string name, std::string phone, std::string address, double balance) : User(id, name, phone, address, balance) {}
  Seller(std::string name, std::string phone, std::string address, double balance) : User(name, phone, address, balance) {}

  void ChangeBalance(double amount) override;

  // checks whether the user is a buyer or a seller
  bool CheckUser() override { return true; };

  void PrintOptions() override;
};

class Buyer : public User
{
public:
  // Buyer(unsigned int id, std::string name, std::string phone, std::string address, double balance) : User(id, name, phone, address, balance) {}
  Buyer(std::string name, std::string phone, std::string address, double balance) : User(name, phone, address, balance) {}
  void ChangeBalance(double amount);

  // void addBidToProduct(Product *product); // could check if balace is enough

  // checks whether the user is a buyer or a seller
  bool CheckUser() override { return false; };

  void PrintOptions() override;
};

#endif // USERS_H header guard