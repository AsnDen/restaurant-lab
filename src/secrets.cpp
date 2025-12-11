#include "secrets.h"

#include <dotenv.h>
#include <plog/Log.h>

#include <string>

std::string loadDBPassword()
{
    PLOGD << "Loading DB password from secrets";
    dotenv::init( "secrets.env" );
    return dotenv::getenv( "DB_PASSWORD", "" );
}
