//
//  main.cpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 13.03.25.
//

#include "Constants.hpp"
#include "Print.hpp"
// #include "Reminders.hpp"
#include "Settings.hpp"
// #include "Spelling.hpp"
#include "sqlite3.h"
#include <iostream>
#include <numeric>
#include <vector>

void cleanInputStream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input. Try again.\n";
}

void mainMenu(sqlite3 *DB) {
    while (true) {
        std::cout << Constants::linesVisualDivider;
        std::cout << "Your reminders:\n";
        printRemindersList(DB);
        std::cout << "Main Menu:\n";
        std::cout << "1 - Add new reminder\n";
        std::cout << "2 - Settings\n";
        std::cout << "3 - Disable/Enable all\n";
        std::cout << "0 - Exit\n";

        while (true) {
            std::cout << "Enter a number to proceed: ";
            int choice{};
            std::cin >> choice;

            if (!std::cin) {
                cleanInputStream();
                continue;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
            case 1:
                addReminder(DB);
                break;
            case 2:
                //                 settings(DB);
                break;
            case 3:
                disableAll(DB);
                break;
            case 0:
                std::cout << "Are you sure? You won't be able to recieve "
                             "reminders (1 - YES; 0 - NO): ";
                std::cin >> choice;
                if (!std::cin) {
                    cleanInputStream();
                    continue;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                '\n');
                if (choice == 1)
                    return;
                else if (choice == 0)
                    break;

                std::cout << "Incorrect. Try again.\n";
                break;

            default:
                std::cout << "Incorrect. Try again.\n";
                continue;
            }
            break;
        }
    }
}

int main() {
    std::string dbLocation{
        "/Users/nikita/SoftwareDevelopment/repo/CLI-RandomReminders/"
        "DerivedData/CLI-RandomReminders/Build/Products/Debug/Reminders.db"};
    sqlite3 *dbReminders{};

    int dbReturnCode{sqlite3_open(dbLocation.data(), &dbReminders)};

    if (dbReturnCode) {
        std::cout << __PRETTY_FUNCTION__ << ": sqlite3_open error- "
                  << sqlite3_errmsg(dbReminders) << '\n';
        sqlite3_close(dbReminders);
    } else {
        std::cout << "Database Reminders.db opened.\n";
    }

    addTableToDB(dbReminders);

    mainMenu(dbReminders);
    //
    //    spellReminders(listReminders);

    dbReturnCode = sqlite3_close(dbReminders);

    if (dbReturnCode) {
        std::cout << __PRETTY_FUNCTION__ << ": sqlite3_close error- "
                  << sqlite3_errmsg(dbReminders) << '\n';
    } else {
        std::cout << "Database Reminders.db closed.\n";
    }

    return 0;
}
