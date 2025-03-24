//
//  Print.cpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 14.03.25.
//

#include "Print.hpp"
#include <iomanip>

int printDB([[maybe_unused]] void *NotUsed, int columns, char **value,
            [[maybe_unused]] char **columnName) {

    for (int i{3}; i < columns; ++i) {
        if (i == 3) {
            std::cout << (std::stoi(value[3]) ? "🔔" : "🔕") << value[3] << '\t';
        } else {
            std::cout << value[i] << '\t';
        }
    }

    std::cout << '\n';

    return 0;
}

void printRemindersList(sqlite3 *DB) {
    std::string sql{"SELECT * FROM REMINDERS;"};

    executeSQL(__PRETTY_FUNCTION__, DB, sql, printDB, nullptr);
}
