class User{
public:
  float get_balance();

  unsigned int get_userid();

  std::string get_name();

  std::string get_phone();

  std::string get_address();  

  void UpdateInformation();


   
private:
  float balance_;
  unsigned int userid_;
  std::string name_;
  std::string phone_;
  std::string address_;
};
class Seller: public User{
public:
  Product* addProductForSale(Product object); 

  void OpenBid(Product* product);

  void CloseBid(Product* product); 

  void sendMessage();
  
private:
  std::vector<Products*> open_bids_;
  std::vector<Products*> closed_bids_;

  
};
class Buyer: public User{
public:
  void addBidToProduct();

  void sendMessage();
private:
  // add more fields as applicable
};