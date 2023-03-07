#include "Product.h"

Product* productFactory(ProductCategory pc, unsigned int sellerId) {
    switch (pc)
    {
    case ProductCategory::Car:
        Car* carObj = new Car;
        carObj->SetSellerId(sellerId);
        return carObj;
        break;
    case ProductCategory::Furniture:
        Furniture* furnitureObj = new Furniture;
        furnitureObj->SetSellerId(sellerId);
        return furnitureObj;
        break;
    case ProductCategory::Book:
        Book* bookObj = new Book;
        bookObj->SetSellerId(sellerId);
        return bookObj;
        break;
    case ProductCategory::Computer:
        Computer* computerObj = new Computer;
        computerObj->SetSellerId(sellerId);
        return computerObj;
        break;
    case ProductCategory::Jewelry:
        Jewelry* JewelryObj = new Jewelry;
        JewelryObj->SetSellerId(sellerId);
        return JewelryObj;
        break;
    default:
        break;
    }
}