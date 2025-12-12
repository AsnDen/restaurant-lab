#include "menu.h"

#include <plog/Log.h>

#include <iostream>
#include <string>
#include <map>

Menu::Menu() : conn{}, hasStarted{true}
{
    PLOGI << "Program is started";
}

bool Menu::isStarted()
{
    return hasStarted;
}

void Menu::closeMenu()
{
    PLOGI << "Program is closed";
    conn.closeConnection();
    hasStarted = false;
}

void Menu::showMainMenu()
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
    switch( chooseOption() ) {
        case 1:
            showAddCategoryMenu();
            break;
        case 2:
            showAddDishMenu();
            break;
        case 3:
            showAddOrderMenu();
            break;
        case 4:
            showAllDishes();
            break;
        case 5:
            showAllOrders();
            break;
        case 6:
            showCategoryIncome();
            break;
        case 7:
            showBestSellers();
            break;
        case 8:
            showAverageCost();
            break;
        case 9:
            showTotalQuantityPerDish();
            break;
        case 0:
            closeMenu();
            break;
        default:
            PLOGD << "Unknown command";
            std::cout << "Unknown command. Try again\n";
    }
}

short int Menu::chooseOption()
{
    short int inp{};
    std::cin >> inp;
    return inp;
}

void Menu::showAddCategoryMenu()
{
    PLOGI << "Add category is used";
    std::cout << "Enter category name: ";
    std::string name{};
    std::cin.ignore();
    std::getline( std::cin, name );
    conn.addCategory( name );
}

void Menu::showAddDishMenu()
{
    PLOGI << "Add dish is used";
    std::cout << "Enter dish name: ";
    std::string name{};
    std::cin.ignore();
    std::getline( std::cin, name );

    std::cout << "Enter category id: ";
    int f_id{};
    std::cin >> f_id;

    std::cout << "Enter price: ";
    long double price{};
    std::cin >> price;

    conn.addDish( name, f_id, price );
}

void Menu::showAddOrderMenu()
{
    PLOGI << "Add order is used";
    std::cout << "Enter dish id: ";
    int f_id{};
    std::cin >> f_id;

    std::cout << "Enter date (YYYY-MM-DD): ";
    std::string date{};
    std::cin >> date;

    std::cout << "Enter quantity: ";
    int quantity{};
    std::cin >> quantity;

    conn.addOrder( f_id, date, quantity );
}

void Menu::showAllDishes()
{
    PLOGI << "Show dishes is chosen";
    std::map<int, Dish> dishes{conn.getAllDishes()};

    for( auto &[key, val] : dishes ) {
        std::cout << "id: " << key << '\n';
        val.printDish();
    }
}

void Menu::showAllOrders()
{
    PLOGI << "Show orders is chosen";
    std::map<int, Order> dishes{conn.getAllOrders()};

    for( auto &[key, val] : dishes ) {
        std::cout << "id: " << key << '\n';
        val.printOrder();
    }
}

void Menu::showCategoryIncome()
{
    PLOGI << "Show income in category is chosen";
    std::map<std::string, long double> categories{
        conn.getTotalCostPerCategory()
    };

    for( auto &[key, val] : categories ) {
        std::cout << "Category: " << key << '\n'
                  << "Income: " << val << '\n'
                  <<  "---------------\n";
    }
}

void Menu::showBestSellers()
{
    PLOGI << "Show top-3 most ordered dishes is chosen";
    std::map<std::string, size_t> bestSellers{conn.getBestSellerDishes()};

    for( auto &[key, val] : bestSellers ) {
        std::cout << "Category: " << key << '\n'
                  << "Total sold: " << val << '\n'
                  <<  "---------------\n";
    }
}

void Menu::showAverageCost()
{
    PLOGI << "Show average order cost is chosen";
    std::cout << "Average price per oder is " << conn.averageOrderPrice();
}

void Menu::showTotalQuantityPerDish()
{
    PLOGI << "Show number of orders per dish chosen";
    std::map<std::string, size_t> dishes{conn.getTotalQuantityPerDish()};

    for( auto &[key, val] : dishes ) {
        std::cout << "Dish: " << key << '\n'
                  << "Total quantity sold: " << val << '\n'
                  <<  "---------------\n";
    }
}
