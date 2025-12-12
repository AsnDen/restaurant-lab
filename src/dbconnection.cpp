#include "dbconnection.h"
#include "secrets.h"

#include <pqxx/pqxx>
#include <plog/Log.h>

#include <string>
#include <stdexcept>
#include <iostream>

DBConnection::DBConnection() : conn{
        "host=localhost "
        "port=5432 "
        "dbname = restaurant_db "
        "user = postgres password = "
        + loadDBPassword()
    }
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
