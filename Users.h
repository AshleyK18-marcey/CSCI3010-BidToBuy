#ifndef USERS_H
#define USERS_H

#include <string>
#include <vector>
#include <iostream>
#include "Product.h"

class User{
public:
  User(unsigned int id, std::string name, std::string phone, std::string address, float balance);
  
  float get_balance() { return balance_; };

  unsigned int get_userid() { return userid_; };

  std::string get_name() { return name_; };

  std::string get_phone() { return phone_; };

  std::string get_address() { return address_; };

  void SetName(std::string newName);

  void SetPhone(std::string newPhone);

  void SetAddress(std::string newAddress);

  void UpdateInformation(std::string infoToChange, std::string newValue);

  friend std::ostream& operator<<(std::ostream& os, const User &u);

private:

  float balance_;
  unsigned int userid_;
  std::string name_;
  std::string phone_;
  std::string address_;

};
class Seller: public User{
public:
  void AddBalanace(float amount);
  
private:
  

  
};
class Buyer: public User{
public:

  void DeductBalanace(float amount);
  
  void addBidToProduct(Product* product); //could check if balace is enough
private:
  
};

#endif // USERS_H ehader guard