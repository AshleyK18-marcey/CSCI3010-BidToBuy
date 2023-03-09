#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <vector>
#include <iostream>

enum class ProductCategory {Car, Furniture, Book, Computer, Jewelry};

class Product{
public:
    Product();
	void MakeBid(float bid, unsigned int user_id);
    unsigned int get_id(){ return product_id_; };
    void OpenBid();
    void CloseBid();
    void SetSellerId(unsigned int newId);
    void SetBuyerId(unsigned int newId);
    void SetUUID(unsigned int newUUID);
    void SetFinalBid(float bid);
    unsigned int get_UUID() { return uuid_; };
    friend std::ostream& operator<<(std::ostream& os, const Product &p);
private:
    const unsigned int product_id_;
    unsigned int uuid_ = 0;
    float current_bid_ = 0;  //dollar value of current highest bid
    std::vector<unsigned int> bidders_;    //id of current highest bidder
    std::vector<float> bid_vals_;
    float final_bid_ = 0;
    unsigned int buyer_id_ = 0;
    unsigned int seller_id_ = 0;
    bool active;
};
class Car: public Product{
public:
    Car();
    std::string GetMake(){ return make_; };
    std::string GetModel(){ return model_; };
    unsigned int GetYear(){ return year_; };
    void SetMake(std::string newMake);
    void SetModel(std::string newModel);
    void SetYear(unsigned int newYear);
private:
    std::string make_;
    std::string model_;
    unsigned int year_;
    const unsigned int product_id_ = 1;
};
class Furniture: public Product{
public:
    Furniture();
    std::string GetMaterial(){ return material_; };
    float GetLength(){ return length_; };
    float GetWidth(){ return width_; };
    float GetHeight(){ return height_; };
    void SetMaterial(std::string newMaterial);
    void SetLength(unsigned int newLength);
    void SetWidth(unsigned int newWidth);
    void SetHeight(unsigned int newHeight);
private:
    std::string material_;
    float length_;
    float width_;
    float height_;
    const unsigned int product_id_ = 2;
};
class Book: public Product{
public:
    Book();
    std::string GetTitle(){ return title_; };
    std::string GetAuthor(){ return author_; };
    void SetTitle(std::string newTitle);
    void SetAuthor(std::string newAuthor);
private:
    std::string title_;
    std::string author_;
    const unsigned int product_id_ = 3;
};
class Computer: public Product{
public:
    Computer();
    float GetScreenSize(){ return screenSize_; };
    float GetProcessorSpeed(){ return processorSpeed_; };
    int GetMemory() { return memory_; };
    void SetScreenSize(float newScreenSize);
    void SetProcessorSpeed(float newSpeed);
    void SetMemory(unsigned int newMemory);
private:
    float screenSize_;
    float processorSpeed_;
    int memory_;
    const unsigned int product_id_ = 4;
};
class Jewelry: public Product{
public:
    Jewelry();
    std::string GetMaterial(){ return material_; };
    int GetNumDiamonds() { return numDiamonds_; };
    void SetMaterial(std::string newMaterial);
    void SetNumDiamonds(unsigned int newNumDiamonds);
private:
    std::string material_;
    int numDiamonds_;
    const unsigned int product_id_ = 5;
};

Product* productFactory(ProductCategory pc, unsigned int sellerId);

#endif  //header gaurd