#include "secrets.h"

#include <dotenv.h>

#include <string>

std::string loadDBPassword()
{
    dotenv::init( "secrets.env" );
    return dotenv::getenv( "DB_PASSWORD", "" );
}
