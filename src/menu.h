#ifndef RESTAURANT_SRC_MENU_H
#define RESTAURANT_SRC_MENU_H

#include "dbconnection.h"

/**
 * Displays menu to the user and
 * allows user to work with program
 */

class Menu
{
    private:
        DBConnection conn;
        bool hasStarted;

        short int chooseOption();
        void showAddCategoryMenu();
        void showAddDishMenu();
        void showAddOrderMenu();
        void showAllDishes();
        void showCategoryIncome();
        void showTopOrders();
        void closeMenu();

    public:
        Menu();
        bool isStarted();
        void showMainMenu();

};

#endif
