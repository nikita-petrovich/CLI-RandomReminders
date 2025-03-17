//
//  Spelling.cpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 14.03.25.
//



#include "Spelling.hpp"
#include "Constants.hpp"
#include <thread>

void spellReminders(std::vector<Reminders>& listReminders)
{
    while(true)
    {
        for (auto& r : listReminders)
        {
            bool notifyTime { std::chrono::steady_clock::now()
                >= (r.getPivotTime() + std::chrono::minutes(r.getNextNotification())) };
            
            if (r.getStatus() && notifyTime)
            {
                //MacOS Terminal uses the keyword 'say' to say the string
                std::string say { "say " };
                say += Constants::keyWordToStartSpell + static_cast<std::string>(r.getRemind());
                std::system(say.data());
                r.setNextNotification(r.getMaxTimeSchedule());
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

