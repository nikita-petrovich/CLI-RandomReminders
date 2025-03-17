//
//  Reminders.cpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 13.03.25.
//

#include "Reminders.hpp"

void Reminders::setStatus(bool enable)
{
    m_enable = enable;
    if (enable)
        {
            setNextNotification(m_maxTimeSchedule);
        }
}

void Reminders::setRemind(std::string_view remind)
{
    m_remind = remind;
}

void Reminders::setMaxTimeSchedule(std::int32_t maxTimeSchedule)
{
    m_maxTimeSchedule = maxTimeSchedule;
    setNextNotification(maxTimeSchedule);
}

void Reminders::setNextNotification(std::int32_t maxTimeSchedule)
{
    m_nextNotification = generateRandomTime(maxTimeSchedule);
    m_pivotTime = std::chrono::steady_clock::now();
}
