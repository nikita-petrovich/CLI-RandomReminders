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

int printDB([[maybe_unused]] void *NotUsed, int columns, char **value,
            [[maybe_unused]] char **columnName);
void printRemindersList(sqlite3 *DB);

#endif /* Print_hpp */
