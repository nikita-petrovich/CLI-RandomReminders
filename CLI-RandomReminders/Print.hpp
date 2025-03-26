//
//  Print.hpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 14.03.25.
//

#ifndef Print_hpp
#define Print_hpp

#include "sqlite3.h"
#include <iostream>

int printTable([[maybe_unused]] void *NotUsed, int columns, char **value,
               [[maybe_unused]] char **columnName);
int printRaw([[maybe_unused]] void *NotUsed, int columns, char **value,
             [[maybe_unused]] char **columnName);
void printSingleReminder(sqlite3 *DB, std::int32_t creationTime);
void printRemindersList(sqlite3 *DB);

#endif /* Print_hpp */
