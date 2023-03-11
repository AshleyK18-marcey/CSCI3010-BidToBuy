#include "Product.h"
/**
    Using factory design pattern to create a new product based on what the seller wants to sell
    @param pc the category of the product 
    @param sellerId the seller associated with the product 
*/
Product *productFactory(ProductCategory pc, unsigned int sellerId)
{
    switch (pc)
    {
    case ProductCategory::Car:
    {
        Car *carObj = new Car;
        carObj->SetSellerId(sellerId);
        return carObj;
        break;
    }
    case ProductCategory::Furniture:
    {
        Furniture *furnitureObj = new Furniture;
        furnitureObj->SetSellerId(sellerId);
        return furnitureObj;
        break;
    }
    case ProductCategory::Book:
    {
        Book *bookObj = new Book;
        bookObj->SetSellerId(sellerId);
        return bookObj;
        break;
    }
    case ProductCategory::Computer:
    {
        Computer *computerObj = new Computer;
        computerObj->SetSellerId(sellerId);
        return computerObj;
        break;
    }
    case ProductCategory::Jewelry:
    {
        Jewelry *JewelryObj = new Jewelry;
        JewelryObj->SetSellerId(sellerId);
        return JewelryObj;
        break;
    }
    default:
    {
        Product *Productobj = new Product;
        return Productobj;
        break;
    }
    }
}

// -----Product-----


/**
    Sets the sellers id to the id specified 

    @param newId the new id 
*/
void Product::SetSellerId(unsigned int newId)
{
    if (newId > 0)
    {
        this->seller_id_ = newId;
    }
}

/**
    Sets the buyer id to the specified one

    @param newId the new id 
*/
void Product::SetBuyerId(unsigned int newId)
{
    if (newId > 0)
    {
        this->buyer_id_ = newId;
    }
}

/**
    When a seller closes a sale this sets the greatest value bid to the final bid that won 

    @param radius The radius of the circle.
    @return The volume of the sphere.
*/
void Product::SetFinalBid(double bid)
{
    if (bid >= 0)
    {
        this->final_bid_ = bid;
    }
    else
    {
        this->final_bid_ = 0;
    }
}

/**
    Displays the product id, the seller and buyer and the final price

    @param os the stream
    @param p the product to display the information of
    @return the stream to display the information to the user
*/
std::ostream &operator<<(std::ostream &os, const Product &p)
{
    os << "ID: " << p.product_id_ << ", seller -> buyer: " << p.seller_id_ << " -> " << p.buyer_id_ << ", final price: " << p.final_bid_;
    return os;
}

// -----Car-----

/**
    Sets the make of the car product

    @param newMake the make of the car to set to
*/
void Car::SetMake(std::string newMake)
{
    if (newMake.length() > 0)
    {
        this->make_ = newMake;
    }
}

/**
    Sets the model of the car

    @param newModel the model of the car to set to
*/
void Car::SetModel(std::string newModel)
{
    if (newModel.length() > 0)
    {
        this->model_ = newModel;
    }
}

/**
    Sets the year of the car

    @param newYear the year of the car to set to
*/
void Car::SetYear(unsigned int newYear)
{
    this->year_ = newYear;
}

// -----Furniture-----

/**
    Sets the material of the furniture product

    @param newMaterial the material of the furniture to set to
*/
void Furniture::SetMaterial(std::string newMaterial)
{
    if (newMaterial.length() > 0)
    {
        this->material_ = newMaterial;
    }
}

/**
    Sets the length dimension of the furniture product

    @param newLength the length to set to
*/
void Furniture::SetLength(unsigned int newLength)
{
    length_ = newLength;
}

/**
    Sets the width dimension of the furniture product

    @param newWidth the width to set to 
*/
void Furniture::SetWidth(unsigned int newWidth)
{
    width_ = newWidth;
}

/**
    Sets the height dimension of the furniture product

    @param newHeight the height to set to 
*/
void Furniture::SetHeight(unsigned int newHeight)
{
    height_ = newHeight;
}