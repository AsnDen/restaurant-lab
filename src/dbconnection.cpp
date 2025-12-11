#include "dbconnection.h"
#include "secrets.h"

#include <pqxx/pqxx>
#include <plog/Log.h>

#include <string>
#include <stdexcept>

DBConnection::DBConnection() : conn{"host=localhost port=5432 dbname=postgres "
                                        "user = postgres password = "
                                        + loadDBPassword()}
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
