#include "Product.h"

Product* productFactory(ProductCategory pc, unsigned int sellerId) {
    switch (pc)
    {
    case ProductCategory::Car:
        {
        Car* carObj = new Car;
        carObj->SetSellerId(sellerId);
        return carObj;
        break;
        }
    case ProductCategory::Furniture:
        {
        Furniture* furnitureObj = new Furniture;
        furnitureObj->SetSellerId(sellerId);
        return furnitureObj;
        break;
        }
    case ProductCategory::Book:
        {
        Book* bookObj = new Book;
        bookObj->SetSellerId(sellerId);
        return bookObj;
        break;
        }
    case ProductCategory::Computer:
        {
        Computer* computerObj = new Computer;
        computerObj->SetSellerId(sellerId);
        return computerObj;
        break;
        }
    case ProductCategory::Jewelry:
        {
        Jewelry* JewelryObj = new Jewelry;
        JewelryObj->SetSellerId(sellerId);
        return JewelryObj;
        break;
        }
    default:
        {
        Product* Productobj = new Product;
        return Productobj;
        break;
        }
    }
}

// -----Product-----

void Product::SetSellerId(unsigned int newId) {
    if (newId > 0)
    {
        this->seller_id_ = newId;
    }
}

// -----Car-----

void Car::SetMake(std::string newMake) {
    if (newMake.length() > 0)
    {
        this->make_ = newMake;
    }
}

void Car::SetModel(std::string newModel) {
    if (newModel.length() > 0)
    {
        this->model_ = newModel;
    }
}

void Car::SetYear(unsigned int newYear) {
    this->year_ = newYear;
}

// -----Furniture-----

void Furniture::SetMaterial(std::string newMaterial) {
    if (newMaterial.length() > 0)
    {
        this->material_ = newMaterial;
    }
}

void Furniture::SetLength(unsigned int newLength) {
    length_ = newLength;
}

void Furniture::SetWidth(unsigned int newWidth) {
    width_ = newWidth;
}

void Furniture::SetHeight(unsigned int newHeight) {
    height_ = newHeight;
}