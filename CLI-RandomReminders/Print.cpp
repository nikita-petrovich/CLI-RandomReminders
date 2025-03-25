//
//  Print.cpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 14.03.25.
//

#include "Print.hpp"

int printDB([[maybe_unused]] void *NotUsed, int columns, char **value,
            [[maybe_unused]] char **columnName) {

    g_CreationTimeList.push_back(std::stoi(value[1]));

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

void printSingleReminder(sqlite3 *DB, std::int32_t creationTime) {
    std::string sql{"SELECT * FROM REMINDERS WHERE CREATION_TIME = "};
    sql.append(std::to_string(creationTime)).append(";");

    executeSQL(__PRETTY_FUNCTION__, DB, sql, printDB, nullptr);
}

void printRemindersList(sqlite3 *DB) {
    std::string sql{"SELECT * FROM REMINDERS;"};

    executeSQL(__PRETTY_FUNCTION__, DB, sql, printDB, nullptr);
}
