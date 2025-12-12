#ifndef RESTAURANT_SRC_DISH_ORDER_H
#define RESTAURANT_SRC_DISH_ORDER_H

#include <string>

/**
 * Classes that represent items in sql table
 */

class Category
{
    private:
        int id;
        std::string name;
    public:
        Category();
        Category( int new_id,
                  std::string new_name );
};

class Dish
{
    protected:
        int id;
        std::string name;
        Category category;
        long double price;
    public:
        Dish();
        Dish( int new_id,
              std::string new_name,
              Category new_category,
              long double new_price );
};

class Order
{
    private:
        int id;
        Dish dish;
        std::string date;
        size_t quantity;
    public:
        Order();
        Order( int new_id,
               Dish new_dish,
               std::string new_date,
               size_t new_quantity );
};

#endif
