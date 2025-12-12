#ifndef RESTAURANT_SRC_DBCONNECTION_H
#define RESTAURANT_SRC_DBCONNECTION_H

#include "dish-order.h"

#include <pqxx/pqxx>

#include <string>
#include <map>

/**
 * Handles connection to a database and transactions
 */

class DBConnection
{
    private:
        pqxx::connection conn;
    public:
        DBConnection();
        void closeConnection();
        void addCategory( const std::string &name );
        void addDish( const std::string &name,
                      const int &f_id,
                      const long double &price );
        void addOrder( const int &f_id,
                       const std::string &date,
                       const int &quantity );

        std::map<int, Category> getAllCategories();
        std::map<int, Dish> getAllDishes();
        std::map<int, Order> getAllOrders();

        std::map<std::string, long double> getTotalCostPerCategory();
        std::map<std::string, size_t> getBestSellerDishes();
        long double averageOrderPrice();
        std::map<std::string, size_t> getTotalQuantityPerDish();
};

#endif
