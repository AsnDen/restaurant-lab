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

    PLOGI << "Connected to a database";
}

void DBConnection::closeConnection()
{
    if( conn.is_open() ) {
        PLOGI << "Closed connection with the database";
        conn.close();
    }
}

void DBConnection::addCategory( const std::string & cat_name )
{
    try {
        pqxx::work txn( conn );
        txn.exec( "INSERT INTO categories (category_name) VALUES (" +
                  txn.quote( cat_name ) + ")" );
        txn.commit();
    } catch( const std::exception& e ) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
