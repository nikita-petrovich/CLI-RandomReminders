//
//  Print.cpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 14.03.25.
//

#include "Print.hpp"
#include <iomanip>

void printSingleReminder(const Reminders& r)
{
    int days { r.getMaxTimeSchedule() / 1440 };
    int hours { r.getMaxTimeSchedule() / 60 - days * 24 };
    int minutes { r.getMaxTimeSchedule() - days * 1440 - hours * 60 };
    
    std::cout << (r.getStatus() ? "🔔" : "🔕") << "  ";
    std::cout << "— time range: " << days << 'd' << hours << 'h' << minutes << 'm' << "  —  ";
    std::cout << r.getRemind() << '\n';
}

void printRemindersList(std::vector<Reminders>& listReminders)
{
    int i { 1 };
    
    for (const auto& r : listReminders)
    {
        std::cout << i++ << ")  ";
        printSingleReminder(r);
    }
}
