#include "dbconnection.h"
#include "secrets.h"
#include "dish-order.h"

#include <pqxx/pqxx>
#include <plog/Log.h>

#include <string>
#include <stdexcept>
#include <iostream>
#include <map>

DBConnection::DBConnection() : conn(
        "host=localhost "
        "port=5432 "
        "dbname = restaurant_db "
        "user = postgres password = "
        + loadDBPassword()
    )
{
    if( !conn.is_open() ) {
        PLOGF << "Failed to connect to a database";
        throw std::runtime_error( "Error while connection to a database" );
    }
    pqxx::work txn( conn );
    txn.exec( "SET lc_messages TO 'C';" );
    txn.commit();

    PLOGI << "Connected to a database";
}

void DBConnection::closeConnection()
{
    if( conn.is_open() ) {
        PLOGI << "Closed connection with the database";
        conn.close();
    }
}

void DBConnection::addCategory( const std::string & name )
{
    try {
        pqxx::work txn( conn );
        txn.exec( "INSERT INTO categories (category_name) VALUES (" +
                  txn.quote( name ) + ")" );
        txn.commit();
        PLOGI_( 1 ) << "Added category " << name << "to a table";
    } catch( const std::exception& e ) {
        PLOGE_( 1 ) << e.what();
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void DBConnection::addDish( const std::string &name,
                            const int &f_id,
                            const long double &price )
{
    try {
        pqxx::work txn( conn );
        txn.exec( "INSERT INTO dishes (name, category_id, price) VALUES ("
                  + txn.quote( name ) + ','
                  + std::to_string( f_id ) + ','
                  + std::to_string( price ) + ")" );
        txn.commit();
        PLOGI_( 1 ) << "Added dish " << name
                    << " with category_id " << f_id
                    << " and price " << price << " to a table";
    } catch( const std::exception& e ) {
        PLOGE_( 1 ) << e.what();
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void DBConnection::addOrder( const int &f_id,
                             const std::string &date,
                             const int &quantity )
{
    try {
        pqxx::work txn( conn );
        txn.exec( "INSERT INTO orders (dish_id, order_date, quantity) VALUES ("
                  + std::to_string( f_id ) + ','
                  + txn.quote( date ) + ','
                  + std::to_string( quantity ) + ")" );
        txn.commit();
        PLOGI_( 1 ) << "Added order of dish with id " << f_id
                    << " with order date " << date
                    << " and quantity " << quantity << " to a table";
    } catch( const std::exception& e ) {
        PLOGE_( 1 ) << e.what();
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

std::map<int, Category> DBConnection::getAllCategories()
{
    PLOGI << "Getting all categories from database";
    std::map<int, Category> categories{};

    try {
        pqxx::work txn( conn );
        pqxx::result res = txn.exec( "SELECT * FROM categories" );

        for( const auto& row : res ) {
            categories[row["id"].as<int>()] = {
                row["category_name"].as<std::string>()
            };
        }

    } catch( const std::exception& e ) {
        PLOGE << e.what();
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return categories;
}

std::map<int, Dish> DBConnection::getAllDishes()
{
    PLOGI << "Getting all dishes from database";
    std::map<int, Dish> dishes{};
    std::map<int, Category> categories{getAllCategories()};

    try {
        pqxx::work txn( conn );
        pqxx::result res = txn.exec( "SELECT * FROM dishes" );

        for( const auto& row : res ) {
            int foreign_id = row["category_id"].as<int>();
            dishes[row["id"].as<int>()] = {row["name"].as<std::string>(),
                                           categories[foreign_id],
                                           row["price"].as<long double>()
                                          };
        }

    } catch( const std::exception& e ) {
        PLOGE << e.what();
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return dishes;
}

std::map<int, Order> DBConnection::getAllOrders()
{
    PLOGI << "Getting all orders from database";
    std::map<int, Order> orders{};
    std::map<int, Dish> dishes{getAllDishes()};

    try {
        pqxx::work txn( conn );
        pqxx::result res = txn.exec( "SELECT * FROM orders" );

        for( const auto& row : res ) {
            int foreign_id = row["dish_id"].as<int>();
            orders[row["order_id"].as<int>()] = {
                dishes[foreign_id],
                row["order_date"].as<std::string>(),
                row["quantity"].as<size_t>()
            };
        }

    } catch( const std::exception& e ) {
        PLOGE << e.what();
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return orders;
}

std::map<std::string, long double> DBConnection::getTotalCostPerCategory()
{
    std::map<std::string, long double> categories{};

    try {
        pqxx::work txn( conn );
        pqxx::result res =
            txn.exec(
                "SELECT category_name, SUM(price) AS total_price\n"
                "FROM categories JOIN dishes\n"
                "ON dishes.category_id = categories.id\n"
                "GROUP BY category_name ORDER BY total_price\n" );

        for( const auto& row : res ) {
            categories[row["category_name"].as<std::string>()] =
                row["total_price"].as<long double>();
        }

        PLOGD << "Got total cost for each category";

    } catch( const std::exception& e ) {
        PLOGE << e.what();
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return categories;
}

std::map<std::string, size_t> DBConnection::getBestSellerDishes()
{
    std::map<std::string, size_t> bestSellers{};
    try {
        pqxx::work txn( conn );
        pqxx::result res =
            txn.exec(
                "SELECT name, SUM(quantity) AS total_quantity\n"
                "FROM dishes JOIN orders ON dishes.id = orders.dish_id\n"
                "GROUP BY name ORDER BY total_quantity DESC LIMIT 3" );

        for( const auto& row : res ) {
            bestSellers[row["name"].as<std::string>()] =
                row["total_quantity"].as<size_t>();
        }

        PLOGD << "Got best seller dishes";

    } catch( const std::exception& e ) {
        PLOGE << e.what();
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return bestSellers;
}

long double DBConnection::averageOrderPrice()
{

    long double average {0};
    try {
        pqxx::work txn( conn );
        pqxx::result res =
            txn.exec(
                "SELECT AVG(total_price) AS avg_price\n"
                "FROM orders" );

        average = res[0]["avg_price"].as<long double>();

        PLOGD << "Got average cost of order";
    } catch( const std::exception& e ) {
        PLOGE << e.what();
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return average;
}

std::map<std::string, size_t> DBConnection::getTotalQuantityPerDish()
{
    std::map<std::string, size_t> ordersQueantity{};
    try {
        pqxx::work txn( conn );
        pqxx::result res =
            txn.exec(
                "SELECT name, SUM(quantity) AS quantity\n"
                "FROM dishes JOIN orders ON dishes.id = orders.dish_id\n"
                "GROUP BY name ORDER BY quantity" );

        for( const auto& row : res ) {
            ordersQueantity[row["name"].as<std::string>()] =
                row["quantity"].as<size_t>();
        }

        PLOGD << "Got total quantity for each dish";

    } catch( const std::exception& e ) {
        PLOGE << e.what();
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return ordersQueantity;
}
