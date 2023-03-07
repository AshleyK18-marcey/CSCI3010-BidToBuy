#include "Product.h"

Product* productFactory(ProductCategory pc) {
    switch (pc)
    {
    case ProductCategory::Car:
        return new Car;
        break;
    case ProductCategory::Furniture:
        return new Furniture;
        break;
    case ProductCategory::Book:
        return new Book;
        break;
    case ProductCategory::Computer:
        return new Computer;
        break;
    case ProductCategory::Jewelry:
        return new Jewelry;
        break;
    default:
        break;
    }
}