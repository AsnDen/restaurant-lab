#include "dish-order.h"

#include <iostream>

// ==============
//    Category

Category::Category() : name{ "NONE" }
{
}

Category::Category( std::string new_name ) : name{ new_name }
{
}

std::string Category::getName()
{
    return name;
}

void Category::printCategory()
{
    std::cout << "Name: " << name << '\n'
              << "---------------\n";
}

// ==============
//      Dish

Dish::Dish() : name {"NONE"}, category{}, price{-1}
{
}

Dish::Dish( std::string new_name,
            Category new_category,
            long double new_price )
    : name{ new_name },
      category{ new_category },
      price{ new_price }
{
}

std::string Dish::getName()
{
    return name;
}

Category Dish::getCategory()
{
    return category;
}

long double Dish::getPrice()
{
    return price;
}

void Dish::printDish()
{
    std::cout << "Name: " << name << '\n'
              << "Category: " << category.getName() << '\n'
              << "---------------\n";
}

// ==============
//    Order

Order::Order() : dish{}, date{"0000-00-00"}, quantity{0}
{
}

Order::Order( Dish new_dish,
              std::string new_date,
              size_t new_quantity )
    : dish{new_dish},
      date{new_date},
      quantity{new_quantity}
{
}

Dish Order::getDish()
{
    return dish;
}

std::string Order::getDate()
{
    return date;
}

size_t Order::getQuantity()
{
    return quantity;
}

void Order::printOrder()
{
    std::cout << "Dish: " << dish.getName() << '\n'
              << "Date: " << date << '\n'
              << "Quantity: " << quantity << '\n'
              << "---------------\n";
}
