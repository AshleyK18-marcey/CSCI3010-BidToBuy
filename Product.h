
class Product{
public:
	void makeBid(float bid, unsigned int user_id);
    unsigned int getID(){ return product_id; };
private:
    const unsigned int product_id;
    float current_bid = 0;  //dollar value of current highest bid
    unsigned int highest_bidder = 0;    //id of current highest bidder
    unsigned int seller_id = 0;
};
class Product1: public Product{

};
class Product2: public Product{

};
