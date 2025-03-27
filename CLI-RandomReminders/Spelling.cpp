//
//  Spelling.cpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 14.03.25.
//

#include "Spelling.hpp"
#include "Settings.hpp"
#include "g_Vars.hpp"
#include <array>
#include <thread>

int getData(void *ptrData, [[maybe_unused]] int columns, char **value,
            [[maybe_unused]] char **columnName) {
    static_cast<std::string *>(ptrData)[0] = value[0];
    static_cast<std::string *>(ptrData)[1] = value[2];
    static_cast<std::string *>(ptrData)[2] = value[4];
    static_cast<std::string *>(ptrData)[3] = value[5];

    return 0;
}

bool checkNotification(sqlite3 *DB, std::string &remind) {
    std::string sql{"SELECT * FROM NOTIFY LIMIT 1"};

    // 0 - ID
    // 1 - NEXT NOTIFICATION
    // 2 - TIME RANGE
    // 3 - remind
    std::array<std::string, 4> data{};
    auto *ptrData{&data};

    executeSQL(__PRETTY_FUNCTION__, DB, sql, getData, ptrData);

    int id = std::stoi(data[0]);
    std::int64_t nextNotification = std::stoi(data[1]);
    std::int32_t timeRange = std::stoi(data[2]);
    remind = data[3];

    std::int64_t timeNow =
        std::chrono::duration_cast<std::chrono::minutes>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();

    if (timeNow >= nextNotification) {

        updateNextNotification(DB, id, timeRange);

        // Prevent spelling accumulated reminders, while app has been closed
        if (timeNow >= nextNotification + timeRange / 2) {
            return 0;
        }
        return 1;
    }

    return 0;
}

void spellReminders(sqlite3 *DB) {
    // We are checking only the first row of the VIEW on the enabled reminders,
    // ordered by NEXT_NOTIFICATION ASC
    std::string sql{"CREATE TEMP VIEW IF NOT EXISTS NOTIFY "
                    "AS SELECT * FROM REMINDERS "
                    "WHERE ENABLE = 1 "
                    "ORDER BY NEXT_NOTIFICATION ASC;"};
    executeSQL(__PRETTY_FUNCTION__, DB, sql, 0, nullptr);

    while (!g_exitApp) {

        std::string remind{};

        if (checkNotification(DB, remind)) {
            // MacOS Terminal uses the keyword 'say' to say the string
            std::string say{"say "};
            say.append("Hey, ").append(remind);
            std::system(say.data());
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
