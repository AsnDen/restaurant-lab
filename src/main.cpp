#include "menu.h"

#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"

#include <iostream>
#include <string>

int main()
{
    // Initialize logger
    plog::init<0>( plog::debug, "..\\logs\\log.txt" );

    Menu menu;
    while( menu.isStarted() ) {
        menu.showMainMenu();
    }

    return 0;
}
