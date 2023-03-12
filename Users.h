#ifndef USERS_H
#define USERS_H

#include <string>
#include <vector>
#include <iostream>
#include "Product.h"

class User
{
public:
  User(unsigned int id, std::string name, std::string phone, std::string address, double balance);

  ~User();

  float get_balance() { return balance_; };

  unsigned int get_userid() { return userid_; };

  std::string get_name() { return name_; };

  std::string get_phone() { return phone_; };

  std::string get_address() { return address_; };

  void SetName(std::string newName);

  void SetPhone(std::string newPhone);

  void SetAddress(std::string newAddress);

  void UpdateInformation();

  virtual void ChangeBalance(double amount) { std::cout << balance_ << std::endl; };

  virtual bool CheckUser() { return false; };

  friend std::ostream &operator<<(std::ostream &os, const User &u);

private:
  unsigned int userid_;

protected:
  double balance_;
  std::string name_;
  std::string phone_;
  std::string address_;
};

class Seller : public User
{
public:
  Seller(unsigned int id, std::string name, std::string phone, std::string address, double balance) : User(id, name, phone, address, balance) {}

  void ChangeBalance(double amount) override;

  bool CheckUser() override;

};

class Buyer : public User
{
public:
  Buyer(unsigned int id, std::string name, std::string phone, std::string address, double balance) : User(id, name, phone, address, balance) {}
  virtual void ChangeBalance(double amount);

  void addBidToProduct(Product *product); // could check if balace is enough

  bool CheckUser() override;

};

#endif // USERS_H ehader guard