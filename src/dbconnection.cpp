#include "dbconnection.h"
#include "secrets.h"

#include <pqxx/pqxx>

#include <string>
#include <stdexcept>

pqxx::connection DBConnection::makeConnection()
{
    std::string conninfo {"host=localhost port=5432 dbname=postgres "
                          "user = postgres password = "
                          + loadDBPassword()};
    pqxx::connection conn{conninfo};

    if( !conn.is_open() ) {
        throw std::runtime_error( "Error while connection to a database" );
    }

    return conn;
}

void DBConnection::closeConnection( pqxx::connection conn )
{
    if( conn.is_open() ) {
        conn.close();
    }
}
