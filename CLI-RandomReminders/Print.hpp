//
//  Print.hpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 14.03.25.
//

#ifndef Print_hpp
#define Print_hpp

#include "Reminders.hpp"
#include "Settings.hpp"
#include <vector>

extern std::vector<std::int32_t> g_CreationTimeList;

int printDB([[maybe_unused]] void *NotUsed, int columns, char **value,
            [[maybe_unused]] char **columnName);
void printSingleReminder(sqlite3 *DB, std::int32_t creationTime);
void printRemindersList(sqlite3 *DB);

#endif /* Print_hpp */
