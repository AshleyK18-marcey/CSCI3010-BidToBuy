class User{
public:
  float get_balance();

  unsigned int get_userid();

  std::string get_name();

  std::string get_phone();

  std::string get_address();  

  void SetName(std::string newName);

  void SetPhone(std::string newPhone);

  void SetAddress(std::string newAddress);

  void UpdateInformation(std::string infoToChange, std::string newValue);

private:

  float balance_;
  unsigned int userid_;
  std::string name_;
  std::string phone_;
  std::string address_;

};
class Seller: public User{
public:
  void addProductForSale(Product* object); 

  void AddBalanace(float amount);

  void OpenBid(Product* product);

  void CloseBid(Product* product); 

 
  
private:
  std::vector<Products*> open_bids_;
  std::vector<Products*> closed_bids_;

  
};
class Buyer: public User{
public:

  void DeductBalanace(float amount);
  
  void addBidToProduct();

  void sendMessage();
private:
  
};