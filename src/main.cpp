#include "menu.h"
#include "dbconnection.h"

#include <iostream>

int main()
{
    bool hasStarted {true};
    connect();
    while( hasStarted ) {
        showMainMenu();
        switch( chooseOption() ) {
            case 1:
                std::cout << "Hey";
                break;
            case 2:
                std::cout << "Day";
                break;
            case 3:
                std::cout << "Day";
                break;
            case 4:
                std::cout << "Day";
                break;
            case 5:
                std::cout << "Day";
                break;
            case 6:
                std::cout << "Day";
                break;
            case 7:
                std::cout << "Day";
                break;
            case 8:
                std::cout << "Day";
                break;
            case 9:
                std::cout << "Day";
                break;
            case 10:
                hasStarted = false;
                break;
            default:
                std::cout << "Unknown command. Try again\n";
        }
    }


    return 0;
}
