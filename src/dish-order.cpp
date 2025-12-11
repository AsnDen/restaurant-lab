#include "dish-order.h"

// ==============
//    Category

Category::Category() : name{ "NONE" }
{
}

Category::Category( std::string new_name ) : name{ new_name }
{
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
