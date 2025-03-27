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

std::string convertTimeRangeToFormat(std::int32_t time) {
    int days{time / 1440};
    int hours{time / 60 - days * 24};
    int minutes{time - days * 1440 - hours * 60};

    std::string format{};

    return format.append(std::to_string(days))
        .append("d")
        .append(std::to_string(hours))
        .append("h")
        .append(std::to_string(minutes))
        .append("m");
}

int printTable([[maybe_unused]] void *NotUsed, [[maybe_unused]] int columns,
               char **value, [[maybe_unused]] char **columnName) {

    g_idAndTimeRangeList.emplace_back(std::stoi(value[0]), std::stoi(value[4]));

    // to print as numbered list
    std::cout << g_idAndTimeRangeList.size() << ") ";
    std::cout << (std::stoi(value[3]) ? "🔔" : "🔕") << ' ';
    std::cout << "| range: "
              << convertTimeRangeToFormat(std::stoi(value[4])) << " |\t";
    std::cout << value[5] << '\n';

    return 0;
}

int printRaw([[maybe_unused]] void *NotUsed, [[maybe_unused]] int columns, char **value,
             [[maybe_unused]] char **columnName) {

    std::cout << (std::stoi(value[3]) ? "🔔" : "🔕") << ' ';
    std::cout << "| range: "
              << convertTimeRangeToFormat(std::stoi(value[4])) << " |\t";
    std::cout << value[5] << '\n';
    std::cout << "Created: " << value[1] << '\n';

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
