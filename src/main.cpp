#include "menu.h"
#include "dbconnection.h"

#include "dbconnection.h"
#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"

#include <iostream>
#include <string>

int main()
{
    bool hasStarted {true};

    // Initialize loggers
    plog::init<0>( plog::debug, "program-log.txt" );
    plog::init<1>( plog::debug, "log.txt" );

    while( hasStarted ) {
        showMainMenu();
        switch( chooseOption() ) {
            case 1:
                PLOGI << "Add category is used";
                break;
            case 2:
                PLOGI << "Add dish is used";
                break;
            case 3:
                PLOGI << "Add order is used";
                break;
            case 4:
                PLOGI << "Show dishes is chosen";
                break;
            case 5:
                PLOGI << "Show orders is chosen";
                break;
            case 6:
                PLOGI << "Show income in category is chosen";
                break;
            case 7:
                PLOGI << "Show top-3 most ordered dished is chosen";
                break;
            case 8:
                PLOGI << "Show average order cost is chosen";
                break;
            case 9:
                PLOGI << "Show number of orders per dish chosen";
                break;
            case 10:
                PLOGI << "Program closed";
                hasStarted = false;
                break;
            default:
                PLOGD << "Unknown command";
                std::cout << "Unknown command. Try again\n";
        }
    }


    return 0;
}
