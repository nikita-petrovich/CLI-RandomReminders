//
//  Settings.hpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 14.03.25.
//

#ifndef Settings_hpp
#define Settings_hpp

#include "Reminders.hpp"
#include "sqlite3.h"
#include <vector>

void executeSQL(std::string_view pretty_function, sqlite3 *DB, std::string &sql,
                int (*callback)(void *, int, char **, char **), void *var);
void addTableToDB(sqlite3 *DB);
void addReminder(sqlite3 *DB);
void settings(sqlite3 *DB);
void disableAll(sqlite3 *DB);
void disableSingleReminder(sqlite3 *DB, std::int32_t creationTime);
void changeText(sqlite3 *DB, std::int32_t creationTime);
void changeTime(sqlite3 *DB, std::int32_t creationTime);
void deleteReminder(sqlite3 *DB, std::int32_t creationTime);

#endif /* Settings_hpp */
