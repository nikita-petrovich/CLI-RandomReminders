//
//  Interface.cpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 26.03.25.
//

#include "Interface.hpp"
#include "Print.hpp"
#include "Settings.hpp"
#include "g_Vars.hpp"
#include <iostream>

std::vector<std::pair<int, std::int32_t>> g_idAndTimeRangeList{};
std::atomic_bool g_exitApp{false};

void cleanInputStream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input. Try again.\n";
}

void mainMenu(sqlite3 *DB) {
    while (true) {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpedantic"
        // clean terminal window
        std::system("printf '\33c\e[3J'");
#pragma clang diagnostic pop

        std::cout << "Your reminders:\n";
        g_idAndTimeRangeList.clear();
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
                settings(DB);
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
                if (choice == 1) {
                    g_exitApp = true;
                    return;
                } else if (choice == 0)
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

void settings(sqlite3 *DB) {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpedantic"
    // clean terminal window
    std::system("printf '\33c\e[3J'");
#pragma clang diagnostic pop

    std::cout << "Your reminders:\n";
    g_idAndTimeRangeList.clear();
    printRemindersList(DB);
    std::size_t reminderIndex{};

    while (true) {
        std::cout << "Which reminder would you like to change? (0 to exit): ";
        std::cin >> reminderIndex;

        if (!std::cin) {
            cleanInputStream();
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }

    if (reminderIndex <= 0)
        return;

    if (reminderIndex > g_idAndTimeRangeList.size()) {
        std::cout << "There is no reminder.\n";
        return;
    }

    // Adjustment for correct indexing in vector
    --reminderIndex;

    while (true) {
        std::cout << "The reminder to change:\n";
        printSingleReminder(DB, g_idAndTimeRangeList[reminderIndex].first);

        std::cout << "1 - Disable/Enable Notification\n";
        std::cout << "2 - Change Text\n";
        std::cout << "3 - Change Time\n";
        std::cout << "4 - Delete\n";
        std::cout << "0 - Back\n";

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
            disableSingleReminder(DB, g_idAndTimeRangeList[reminderIndex]);
            break;
        case 2:
            changeText(DB, g_idAndTimeRangeList[reminderIndex].first);
            break;
        case 3:
            changeTime(DB, g_idAndTimeRangeList[reminderIndex]);
            break;
        case 4:
            deleteReminder(DB, g_idAndTimeRangeList[reminderIndex].first);
            return;
        case 0:
            return;

        default:
            std::cout << "Incorrect. Try again.\n";
            continue;
        }
    }
}
