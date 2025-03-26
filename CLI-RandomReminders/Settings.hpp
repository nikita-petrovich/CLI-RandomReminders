//
//  Settings.hpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 14.03.25.
//

#ifndef Settings_hpp
#define Settings_hpp

#include "sqlite3.h"
#include <iostream>

void executeSQL(std::string_view pretty_function, sqlite3 *DB, std::string &sql,
                int (*callback)(void *, int, char **, char **), void *var);
void addTableToDB(sqlite3 *DB);
void addReminder(sqlite3 *DB);
void settings(sqlite3 *DB);
void disableAll(sqlite3 *DB);
void disableSingleReminder(sqlite3 *DB,
                           std::pair<int, std::int32_t> &idAndTimeRange);
void changeText(sqlite3 *DB, int id);
void changeTime(sqlite3 *DB, std::pair<int, std::int32_t> &idAndTimeRange);
void deleteReminder(sqlite3 *DB, int id);
void updateNextNotification(sqlite3 *DB, int id, std::int32_t timeRange);

#endif /* Settings_hpp */
