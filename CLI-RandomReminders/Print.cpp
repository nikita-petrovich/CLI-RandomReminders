//
//  Print.cpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 14.03.25.
//

#include "Print.hpp"
#include "Settings.hpp"
#include "g_Vars.hpp"
#include <iostream>

int printTable([[maybe_unused]] void *NotUsed, int columns, char **value,
               [[maybe_unused]] char **columnName) {

    g_idAndTimeRangeList.emplace_back(std::stoi(value[0]), std::stoi(value[4]));

    // to print as numbered list
    std::cout << g_idAndTimeRangeList.size() << ") ";

    for (int i{0}; i < columns; ++i) {
        if (i == 3) {
            std::cout << (std::stoi(value[3]) ? "🔔" : "🔕") << value[3]
                      << '\t';
        } else {
            std::cout << value[i] << '\t';
        }
    }

    std::cout << '\n';

    return 0;
}

int printRaw([[maybe_unused]] void *NotUsed, int columns, char **value,
             [[maybe_unused]] char **columnName) {

    for (int i{0}; i < columns; ++i) {
        if (i == 3) {
            std::cout << (std::stoi(value[3]) ? "🔔" : "🔕") << value[3]
                      << '\t';
        } else {
            std::cout << value[i] << '\t';
        }
    }

    std::cout << '\n';

    return 0;
}

void printSingleReminder(sqlite3 *DB, int id) {
    std::string sql{"SELECT * FROM REMINDERS WHERE ID = "};
    sql.append(std::to_string(id)).append(";");

    executeSQL(__PRETTY_FUNCTION__, DB, sql, printRaw, nullptr);
}

void printRemindersList(sqlite3 *DB) {
    std::string sql{"SELECT * FROM REMINDERS;"};

    executeSQL(__PRETTY_FUNCTION__, DB, sql, printTable, nullptr);
}
