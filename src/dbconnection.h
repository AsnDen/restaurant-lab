#ifndef RESTAURANT_SRC_DBCONNECTION_H
#define RESTAURANT_SRC_DBCONNECTION_H

#include <pqxx/pqxx>

#include <string>

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
        void addCategory( const std::string &cat_name );
};

#endif
