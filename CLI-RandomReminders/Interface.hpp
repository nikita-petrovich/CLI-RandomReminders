//
//  Interface.hpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 26.03.25.
//

#ifndef Interface_hpp
#define Interface_hpp

#include "sqlite3.h"

void settings(sqlite3 *DB);
void mainMenu(sqlite3 *DB);
void cleanInputStream();

#endif /* Interface_hpp */
