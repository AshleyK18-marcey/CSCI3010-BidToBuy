#ifndef PRODUCTFACTORY_H
#define PRODUCTFACTORY_H
#include "Product.h"

class ProductFactory
{
public:
    static Product *productFactory(ProductCategory pc, User *seller, bool user_input)
    {
        Product *product = NULL;
        switch (pc)
        {
        case ProductCategory::Car:
        {
            Car *carObj = new Car;
            carObj->SetSeller(seller);
            product = carObj;
            break;
        }
        case ProductCategory::Furniture:
        {
            Furniture *furnitureObj = new Furniture;
            furnitureObj->SetSeller(seller);
            product = furnitureObj;
            break;
        }
        case ProductCategory::Book:
        {
            Book *bookObj = new Book;
            bookObj->SetSeller(seller);
            product = bookObj;
            break;
        }
        case ProductCategory::Computer:
        {
            Computer *computerObj = new Computer;
            computerObj->SetSeller(seller);
            product = computerObj;
            break;
        }
        case ProductCategory::Jewelry:
        {
            Jewelry *JewelryObj = new Jewelry;
            JewelryObj->SetSeller(seller);
            product = JewelryObj;
            break;
        }
        default:
        {
            std::cout << "Invalid" << std::endl;
            break;
        }
        }
        if(user_input){
            product->AssembleProduct();
        }
        
        return product;
    }
};

#endif