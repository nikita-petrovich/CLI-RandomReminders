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

void executeSQL(std::string_view pretty_function, sqlite3 *DB, std::string &sql,
                int (*callback)(void *, int, char **, char **), void *var);
void addTableToDB(sqlite3 *DB);
void addReminder(sqlite3 *DB);
void settings(std::vector<Reminders> &listReminders);
void disableAll(sqlite3 *DB);
void disableSingleReminder(sqlite3 *DB);
void changeText(sqlite3 *DB);
void changeTime(sqlite3 *DB);
void deleteReminder(sqlite3 *DB, std::size_t indexDelete);

#endif /* Settings_hpp */
