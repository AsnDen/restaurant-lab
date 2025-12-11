#ifndef RESTAURANT_SRC_DBCONNECTION_H
#define RESTAURANT_SRC_DBCONNECTION_H

#include <pqxx/pqxx>

/**
 * Handles connection to a database
 */

class DBConnection
{
    private:
        pqxx::connection conn;
    public:
        pqxx::connection makeConnection();
        void closeConnection( pqxx::connection conn );
};

#endif
