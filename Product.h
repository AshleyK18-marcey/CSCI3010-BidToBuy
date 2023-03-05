#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>

class Product{
public:
	void MakeBid(float bid, unsigned int user_id);
    unsigned int GetID(){ return product_id_; };
private:
    const unsigned int product_id_;
    float current_bid_ = 0;  //dollar value of current highest bid
    unsigned int highest_bidder_ = 0;    //id of current highest bidder
    unsigned int seller_id_ = 0;
};
class Car: public Product{
public:
    std::string GetMake(){ return make_; };
    std::string GetModel(){ return model_; };
    unsigned int GetYear(){ return year_; };
private:
    std::string make_;
    std::string model_;
    unsigned int year_;
    const unsigned int product_id_ = 1;
};
class Furniture: public Product{
public:
    std::string GetMaterial(){ return material_; };
    float GetLength(){ return length_; };
    float GetWidth(){ return width_; };
    float GetHeight(){ return height_; };
private:
    std::string material_;
    float length_;
    float width_;
    float height_;
    const unsigned int product_id_ = 2;
};
class Book: public Product{
public:
    std::string GetTitle(){ return title_; };
    std::string GetAuthor(){ return author_; };
private:
    std::string title_;
    std::string author_;
    const unsigned int product_id_ = 3;
};
class Computer: public Product{
public:
    float GetScreenSize(){ return screenSize_; };
    float GetProcessorSpeed(){ return processorSpeed_; };
    int GetMemory() { return memory_; };
private:
    float screenSize_;
    float processorSpeed_;
    int memory_;
    const unsigned int product_id_ = 4;
};
class Jewelry: public Product{
public:
    std::string GetMaterial(){ return material_; };
    int GetNumDiamonds() { return numDIamonds_; };
private:
    std::string material_;
    int numDIamonds_;
    const unsigned int product_id_ = 5;
};

#endif  //header gaurd