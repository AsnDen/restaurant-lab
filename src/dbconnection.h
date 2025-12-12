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
        void addCategory( const std::string &name );
        void addDish( const std::string &name,
                      const int &f_id,
                      const long double &price );
        void addOrder( const int &f_id,
                       const std::string &date,
                       const int &quantity );
};

#endif
