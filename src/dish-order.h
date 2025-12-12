#ifndef RESTAURANT_SRC_DISH_ORDER_H
#define RESTAURANT_SRC_DISH_ORDER_H

#include <string>

/**
 * Classes that represent items in sql table
 */

class Category
{
    private:
        std::string name;
    public:
        Category();
        Category( std::string new_name );

        std::string getName();

        void printCategory();
};

// Dishes start

class Dish
{
    protected:
        std::string name;
        Category category;
        long double price;
    public:
        Dish();
        Dish( std::string new_name,
              Category new_category,
              long double new_price );

        std::string getName();
        Category getCategory();
        long double getPrice();

        void printDish();
};

class MainCourse : public Dish
{
    public:
        MainCourse( std::string new_name,
                    long double new_price );
};

class Dessert : public Dish
{
    public:
        Dessert( std::string new_name,
                 long double new_price );
};

// Dishes end

class Order
{
    private:
        Dish dish;
        std::string date;
        size_t quantity;
    public:
        Order();
        Order( Dish new_dish,
               std::string new_date,
               size_t new_quantity );

        Dish getDish();
        std::string getDate();
        size_t getQuantity();

        void printOrder();
};

template<typename T1, typename T2>
class Pair
{
    private:
        T1 first;
        T2 second;

    public:
        Pair( const T1& f, const T2& s ) : first( f ), second( s ) {}

        const T1 &getFirst() const {
            return first;
        }
        const T2 &getSecond() const {
            return second;
        }
};

#endif
