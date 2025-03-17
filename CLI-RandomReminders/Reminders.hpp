//
//  Reminders.hpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 13.03.25.
//

#ifndef Reminders_hpp
#define Reminders_hpp

#include "Random.hpp"
#include <iostream>
#include <chrono>

class Reminders
{
private:
    
    static constexpr std::int32_t m_defaultMinTimeSchedule { 1 };
    // 7 days - 10080min
    static constexpr std::int32_t m_defaultMaxTimeSchedule { 10080 };
    
    bool m_enable { true };
    std::string m_remind {};
    
    std::chrono::time_point<std::chrono::steady_clock> m_pivotTime {
        std::chrono::steady_clock::now() };
    
    std::int32_t m_maxTimeSchedule { m_defaultMaxTimeSchedule };
    std::int32_t m_nextNotification {};
    
    std::int32_t generateRandomTime(std::int32_t max)
    {
        return Random::get(m_defaultMinTimeSchedule, max);
    }
    
public:
    Reminders() = delete;
    
    explicit Reminders(std::string_view remind)
    : Reminders { remind, m_defaultMaxTimeSchedule }
    {}
    
    explicit Reminders(std::string_view remind, std::int32_t maxTimeSchedule)
    : m_remind { remind }
    , m_maxTimeSchedule { maxTimeSchedule }
    , m_nextNotification { generateRandomTime(maxTimeSchedule) }
    {}
    
    ~Reminders()
    {}
    
    bool getStatus() const {return m_enable; }
    std::string_view getRemind() const { return m_remind; }
    std::int32_t getNextNotification() const { return m_nextNotification; }
    std::int32_t getMaxTimeSchedule() const { return m_maxTimeSchedule; }
    auto getPivotTime () const { return m_pivotTime; }
    
    void setStatus(bool enable);
    void setRemind(std::string_view remind);
    void setMaxTimeSchedule(std::int32_t maxTimeSchedule);
    void setNextNotification(std::int32_t maxTimeSchedule);
    
};

#endif /* Reminders_hpp */
