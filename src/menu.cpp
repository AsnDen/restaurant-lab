#include "menu.h"
#include <iostream>

void showMainMenu()
{
    std::cout << "====================\n"
                 "1.  Add category\n"
                 "2.  Add dish\n"
                 "3.  Add order\n"
                 "4.  Show all dishes\n"
                 "5.  Show all orders\n"
                 "6.  Show income in category\n"
                 "7.  Show top-3 most ordered dishes\n"
                 "8.  Show average cost of order\n"
                 "9.  Show number of orders for each dish\n"
                 "0.  Exit program\n"
                 "====================\n"
                 "Shoose option: ";
}

short int chooseOption()
{
    short int inp{};
    std::cin >> inp;
    return inp;
}
