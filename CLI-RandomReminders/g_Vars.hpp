//
//  g_Vars.hh
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 26.03.25.
//

#ifndef g_Vars_h
#define g_Vars_h

#include <atomic>
#include <vector>

extern std::vector<std::pair<int, std::int32_t>> g_idAndTimeRangeList;
extern std::atomic_bool g_exitApp;

#endif /* g_Vars_h */
