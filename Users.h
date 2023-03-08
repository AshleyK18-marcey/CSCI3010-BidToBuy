#ifndef USERS_H
#define USERS_H

#include <string>
#include <vector>
#include "Product.h"

class User{
public:
  User(unsigned int id, std::string name, std::string phone, std::string address, float balance);
  
  float get_balance();

  unsigned int get_userid();

  std::string get_name();

  std::string get_phone();

  std::string get_address();  

  void SetName(std::string newName);

  void SetPhone(std::string newPhone);

  void SetAddress(std::string newAddress);

  void UpdateInformation(std::string , std::string newValue);

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