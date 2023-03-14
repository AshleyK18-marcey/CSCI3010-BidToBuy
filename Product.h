#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <vector>
#include <iostream>
#include "Users.h"
//#include "helpers.cpp"
//#include "ProductFactory.h"
//#include "ProductFactory.h"

std::string promptValidString(std::string prompt);
int promptValidInt(std::string prompt);
float promptValidFloat(std::string prompt);
bool isNumeric(std::string const &str);
bool isFloat( std::string myString );

enum class ProductCategory
{
    Car,
    Furniture,
    Book,
    Computer,
    Jewelry
};
enum Condition
{
    New,
    Used_VeryGood,
    Used_Good,
    Used_okay
};

class Product
{
public:
    Product(){};

    void MakeBid(double bid, User *buyer);

    void StartBid(double bid);

    ProductCategory get_type() const { return product_type_; };

    virtual std::string Stringify();

    void OpenBid();
    bool CloseBid();
    User *get_seller() { return seller_ptr_; };

    User *get_buyer() { return buyer_ptr_; };
    bool get_active() { return active; };

    std::string get_title() { return title_; };

    std::string get_condition();

    std::vector<User *> get_bidders() { return bidders_; };

    void SetTitle(std::string newTitle);

    void SetSeller(User *seller);

    void SetBuyer(User *buyer);

    void SetUUID(unsigned int newUUID);

    void SetFinalBid(double bid);
    float get_last_bid();

    bool SetCondition(int current_condition);

    double get_final_bid() const
    {
        return final_bid_;
    }
    unsigned int get_UUID() { return uuid_; };
    // friend std::ostream &operator<<(std::ostream &os, const Product &p);

    virtual void AssembleProduct() = 0;

    virtual void AssignMetaData(std::string title, std::string meta1, std::string meta2, std::string meta3, std::string meta4, std::string condition) = 0;

    virtual std::string get_type_string() = 0;

protected:
    std::string title_;
    Condition current_condition_;
    ProductCategory product_type_;
    unsigned int uuid_ = 0;
    float current_bid_ = 0;       // dollar value of current highest bid
    std::vector<User *> bidders_; // id of current highest bidder
    std::vector<double> bid_vals_;
    float final_bid_ = 0;
    User *buyer_ptr_ = NULL;
    User *seller_ptr_ = NULL;
    bool active;
};
class Car : public Product
{
public:
    void AssembleProduct();
    void AssignMetaData(std::string title, std::string make, std::string model, std::string year, std::string blank, std::string condition);
    Car(){};
    std::string GetMake() { return make_; };
    std::string GetModel() { return model_; };
    unsigned int GetYear() { return year_; };
    void SetMake(std::string newMake);
    void SetModel(std::string newModel);
    void SetYear(unsigned int newYear);
    std::string get_type_string() override { return "Car"; };
    std::string Stringify() override;

private:
    std::string make_;
    std::string model_;
    unsigned int year_;
    const unsigned int product_id_ = 1;
};
class Furniture : public Product
{
public:
    void AssembleProduct();
    void AssignMetaData(std::string title, std::string material, std::string length, std::string width, std::string height, std::string condition);
    Furniture(){};
    std::string GetMaterial() { return material_; };
    float GetLength() { return length_; };
    float GetWidth() { return width_; };
    float GetHeight() { return height_; };
    void SetMaterial(std::string newMaterial);
    void SetLength(float newLength);
    void SetWidth(float newWidth);
    void SetHeight(float newHeight);
    std::string get_type_string() override { return "Furniture"; };
    std::string Stringify() override;

private:
    std::string material_;
    float length_;
    float width_;
    float height_;
    const unsigned int product_id_ = 2;
};
class Book : public Product
{
public:
    void AssembleProduct();
    void AssignMetaData(std::string title, std::string book_title, std::string author, std::string blank, std::string blank2, std::string condition);
    Book(){};
    std::string GetBookTitle() { return book_title_; };
    std::string GetAuthor() { return author_; };
    void SetBookTitle(std::string newTitle);
    void SetAuthor(std::string newAuthor);
    std::string get_type_string() override { return "Book"; };
    std::string Stringify() override;

private:
    std::string book_title_;
    std::string author_;
    const unsigned int product_id_ = 3;
};
class Computer : public Product
{
public:
    void AssembleProduct();
    void AssignMetaData(std::string title, std::string screensize, std::string processorSpeed, std::string memory, std::string blank, std::string condition);
    Computer(){};
    float GetScreenSize() { return screenSize_; };
    float GetProcessorSpeed() { return processorSpeed_; };
    int GetMemory() { return memory_; };
    void SetScreenSize(float newScreenSize);
    void SetProcessorSpeed(float newSpeed);
    void SetMemory(unsigned int newMemory);
    std::string get_type_string() override { return "Computer"; };
    std::string Stringify() override;

private:
    float screenSize_;
    float processorSpeed_;
    int memory_;
    const unsigned int product_id_ = 4;
};
class Jewelry : public Product
{
public:
    void AssembleProduct();
    void AssignMetaData(std::string title, std::string material, std::string numDiamonds, std::string blank, std::string blank2, std::string condition);
    Jewelry(){};
    std::string GetMaterial() { return material_; };
    int GetNumDiamonds() { return numDiamonds_; };
    void SetMaterial(std::string newMaterial);
    void SetNumDiamonds(unsigned int newNumDiamonds);
    std::string get_type_string() override { return "Jewelry"; };
    std::string Stringify() override;

private:
    std::string material_;
    int numDiamonds_;
    const unsigned int product_id_ = 5;
};

#endif // header gaurd