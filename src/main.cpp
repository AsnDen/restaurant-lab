#include "menu.h"

#include <plog/Log.h>
#include "plog/Initializers/RollingFileInitializer.h"

#include <iostream>
#include <string>

int main()
{
    // Initialize loggers
    plog::init<0>( plog::debug, "..\\logs\\program-log.txt" );
    plog::init<1>( plog::debug, "..\\logs\\log.txt" );

    Menu menu;
    while( menu.isStarted() ) {
        menu.showMainMenu();
    }


    return 0;
}
