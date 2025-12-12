#include "dish-order.h"

// ==============
//    Category

Category::Category() : id{-1}, name{ "NONE" }
{
}

Category::Category( int new_id,
                    std::string new_name )
    : id{new_id},
      name{ new_name }
{
}

// ==============
//      Dish

Dish::Dish() : id{-1}, name {"NONE"}, category{}, price{-1}
{
}

Dish::Dish( int new_id,
            std::string new_name,
            Category new_category,
            long double new_price )
    : id{new_id},
      name{ new_name },
      category{ new_category },
      price{ new_price }
{
}

// ==============
//    Order

Order::Order() : id{-1}, dish{}, date{"0000-00-00"}, quantity{0}
{
}

Order::Order( int new_id,
              Dish new_dish,
              std::string new_date,
              size_t new_quantity )
    : id{new_id},
      dish{new_dish},
      date{new_date},
      quantity{new_quantity}
{
}
