//
//  Settings.cpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 14.03.25.
//

#include "Settings.hpp"
#include "Constants.hpp"
#include "Print.hpp"

void cleanInputStream();

void executeSQL(std::string_view pretty_function, sqlite3 *DB, std::string &sql,
                int (*callback)(void *, int, char **, char **) = 0,
                void *var = nullptr) {

    char *error{};
    int dbReturnCode{sqlite3_exec(DB, sql.data(), callback, var, &error)};

    if (dbReturnCode) {
        std::cout << pretty_function << ": executeSQL() error - " << error
                  << '\n';
        sqlite3_free(error);
    } else {
        std::cout << pretty_function << ": success.\n";
    }
}

void addTableToDB(sqlite3 *DB) {
    std::string sql{"CREATE TABLE IF NOT EXISTS REMINDERS ("
                    "ID INTEGER PRIMARY KEY ASC,"
                    "CREATION_TIME INT DEFAULT (unixepoch()),"
                    "NEXT_NOTIFICATION INT DEFAULT (10080),"
                    "ENABLE INT DEFAULT (1),"
                    "TIME_RANGE INT DEFAULT (10080),"
                    "REMINDER STRING NOT NULL);"};

    executeSQL(__PRETTY_FUNCTION__, DB, sql);
}

void addReminder(sqlite3 *DB) {
    std::cout << Constants::linesVisualDivider;
    std::cout << "Write your reminder: ";
    std::string reminder{};
    std::getline(std::cin >> std::ws, reminder);

    std::string sql{"INSERT INTO REMINDERS (REMINDER) VALUES ('"};
    sql.append(reminder).append("');");

    executeSQL(__PRETTY_FUNCTION__, DB, sql);
}

// void disableSingleReminder(sqlite3 *DB){
//     reminder.getStatus() ? reminder.setStatus(false) :
//     reminder.setStatus(true);
// }

int getStatus(void *currentStatus, [[maybe_unused]] int columns, char **value,
              [[maybe_unused]] char **columnName) {

    *static_cast<int *>(currentStatus) = std::stoi(value[0]);

    return 0;
}

void disableAll(sqlite3 *DB) {
    // if the first reminder is enabeled, disable all. And vice-versa
    std::string sql{"SELECT ENABLE FROM REMINDERS LIMIT 1;"};
    int currentStatus{0};
    int *ptrCurrentStatus{&currentStatus};
    executeSQL(__PRETTY_FUNCTION__, DB, sql, getStatus, ptrCurrentStatus);

    std::string newStatus{};
    currentStatus ? newStatus = "0" : newStatus = "1";
    sql = "UPDATE OR REPLACE REMINDERS SET ENABLE='";
    sql.append(newStatus).append("';");

    executeSQL(__PRETTY_FUNCTION__, DB, sql);
}

// void changeText(Reminders& reminder)
//{
//     std::cout << Constants::linesVisualDivider;
//     std::cout << "Write new text: ";
//     std::string newText {};
//     std::getline(std::cin >> std::ws, newText);
//
//     reminder.setRemind(newText);
//
//     std::cout << "New text accepted.\n";
// }
//
// std::int32_t convertUserInputTime(std::string& str)
//{
//     int days {};
//     int hours {};
//     int minutes {};
//     char delimeter {};
//
//     //Erase all whitespaces to properly check for correctness
//     str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
//
//     //Check for the right format
//     if (std::tolower(str[2]) != 'd' || std::tolower(str[5]) != 'h'
//         || std::tolower(str[8]) != 'm' || str.size() != 9)
//         return -1;
//
//     std::stringstream ss { str };
//     ss >> days >> delimeter >> hours >> delimeter >> minutes;
//
//     return days * 1440 + hours * 60 + minutes;
// }
//
// void changeTime(Reminders& reminder)
//{
//     std::int32_t newTime {};
//
//     while (true)
//     {
//         std::cout << Constants::linesVisualDivider;
//         std::cout << "Write new time using format 00d00h00m (e.g. 01d00h23m):
//         "; std::string newTimeString {}; std::getline(std::cin >> std::ws,
//         newTimeString);
//
//         newTime = convertUserInputTime(newTimeString);
//
//         if (newTime == -1)
//             {
//                 std::cout << "Incorrect input. Try again.\n";
//                 continue;
//             }
//         break;
//     }
//
//
//     reminder.setMaxTimeSchedule(newTime);
//
//     std::cout << "New time accepted.\n";
// }
//
// void deleteReminder(std::vector<Reminders>& listReminders, std::size_t
// indexDelete)
//{
//     listReminders
//         .erase(listReminders.begin() +
//         static_cast<std::ptrdiff_t>(indexDelete));
//
//     std::cout << "The reminder deleted.\n";
// }
//
// void settings(std::vector<Reminders>& listReminders)
//{
//     std::cout << Constants::linesVisualDivider;
//     printRemindersList(listReminders);
//     std::size_t reminderIndex {};
//
//     while(true)
//     {
//         std::cout << "Which reminder would you like to change? (0 to exit):
//         "; std::cin >> reminderIndex;
//
//         if(!std::cin)
//         {
//             cleanInputStream();
//             continue;
//         }
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//         break;
//     }
//
//     if (reminderIndex <= 0)
//         return;
//
//     if (reminderIndex > listReminders.size())
//     {
//         std::cout << "There is no reminder.\n";
//         return;
//     }
//
//     //Adjustment for correct indexing in vector
//     --reminderIndex;
//
//     while(true)
//     {
//         std::cout << Constants::linesVisualDivider;
//         std::cout << "The reminder to change:\n";
//         printSingleReminder(listReminders[reminderIndex]);
//
//         std::cout << "1 - Disable/Enable Notification\n";
//         std::cout << "2 - Change Text\n";
//         std::cout << "3 - Change Time\n";
//         std::cout << "4 - Delete\n";
//         std::cout << "0 - Back\n";
//
//         std::cout << "Enter a number to proceed: ";
//         int choice {};
//         std::cin >> choice;
//
//         if(!std::cin)
//         {
//             cleanInputStream();
//             continue;
//         }
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//         switch (choice) {
//             case 1:
//                 disableSingleReminder(listReminders[reminderIndex]);
//                 break;
//             case 2:
//                 changeText(listReminders[reminderIndex]);
//                 break;
//             case 3:
//                 changeTime(listReminders[reminderIndex]);
//                 break;
//             case 4:
//                 deleteReminder(listReminders, reminderIndex);
//                 return;
//             case 0:
//                 return;
//
//             default:
//                 std::cout << "Incorrect. Try again.\n";
//                 continue;
//         }
//     }
//}
