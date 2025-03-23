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

void addTableToDB(sqlite3 *DB);
void addReminder(sqlite3 *DB);
void settings(std::vector<Reminders>& listReminders);
void disableAll(std::vector<Reminders>& listReminders);
void disableSingleReminder(Reminders& reminder);
void changeText(Reminders& reminder);
void changeTime(Reminders& reminder);
void deleteReminder(std::vector<Reminders>& listReminders, std::size_t indexDelete);

#endif /* Settings_hpp */
