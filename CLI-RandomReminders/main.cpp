//
//  main.cpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 13.03.25.
//

#include "Interface.hpp"
#include "Settings.hpp"
#include "Spelling.hpp"
#include "sqlite3.h"
#include <iostream>

int main() {
    std::string dbLocation{
        "/Users/nikita/SoftwareDevelopment/repo/CLI-RandomReminders/"
        "DerivedData/CLI-RandomReminders/Build/Products/Debug/Reminders.db"};
    sqlite3 *dbReminders{};

    int dbReturnCode{sqlite3_open(dbLocation.data(), &dbReminders)};
    if (dbReturnCode) {
        std::cout << __PRETTY_FUNCTION__ << ": sqlite3_open error - "
                  << sqlite3_errmsg(dbReminders) << '\n';
        sqlite3_close(dbReminders);
    } /*else {
        std::cout << "Database Reminders.db opened.\n";
    }*/

    addTableToDB(dbReminders);

    mainMenu(dbReminders);
    spellReminders(dbReminders);

    dbReturnCode = sqlite3_close(dbReminders);
    if (dbReturnCode) {
        std::cout << __PRETTY_FUNCTION__ << ": sqlite3_close error - "
                  << sqlite3_errmsg(dbReminders) << '\n';
    } /*else {
        std::cout << "Database Reminders.db closed.\n";
    }*/

    return 0;
}
