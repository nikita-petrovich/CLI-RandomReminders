//
//  Settings.cpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 14.03.25.
//

#include "Settings.hpp"
#include "Random.hpp"
#include "g_Vars.hpp"
#include <sstream>

void cleanInputStream();

void executeSQL(std::string_view pretty_function, sqlite3 *DB, std::string &sql,
                int (*callback)(void *, int, char **, char **) = 0,
                void *var = nullptr) {

    char *error{};
    int dbReturnCode{sqlite3_exec(DB, sql.data(), callback, var, &error)};

    if (dbReturnCode) {
        std::cout << pretty_function << ": executeSQL() error - " << error
                  << '\n';
        sqlite3_free(error);
    } /*else {
        std::cout << pretty_function << ": success.\n";
    }*/
}

void addTableToDB(sqlite3 *DB) {
    std::string sql{
        "CREATE TABLE IF NOT EXISTS REMINDERS ("
        "ID INTEGER PRIMARY KEY ASC,"
        "CREATION_TIME INT DEFAULT (datetime('now')),"
        "NEXT_NOTIFICATION INT DEFAULT (unixepoch()),"
        "ENABLE INT DEFAULT (1),"
        "TIME_RANGE INT DEFAULT (10080)," // minutes (10080 - 7 days)
        "REMINDER STRING NOT NULL);"};

    executeSQL(__PRETTY_FUNCTION__, DB, sql);
}

void addReminder(sqlite3 *DB) {
    std::cout << "Write your reminder: ";
    std::string reminder{};
    std::getline(std::cin >> std::ws, reminder);

    std::int64_t timeNow =
        std::chrono::duration_cast<std::chrono::minutes>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();

    std::int64_t nextNotification{Random::get(1, 10080) + timeNow};

    std::string sql{
        "INSERT INTO REMINDERS (REMINDER, NEXT_NOTIFICATION) VALUES ('"};
    sql.append(reminder)
        .append("', '")
        .append(std::to_string(nextNotification))
        .append("');");

    executeSQL(__PRETTY_FUNCTION__, DB, sql);
}

int getStatus(void *currentStatus, [[maybe_unused]] int columns, char **value,
              [[maybe_unused]] char **columnName) {

    *static_cast<int *>(currentStatus) = std::stoi(value[0]);

    return 0;
}

void disableSingleReminder(sqlite3 *DB,
                           std::pair<int, std::int32_t> &idAndTimeRange) {
    std::string sql{"SELECT ENABLE FROM REMINDERS WHERE ID = "};
    sql.append(std::to_string(idAndTimeRange.first)).append(";");
    int currentStatus{0};
    int *ptrCurrentStatus{&currentStatus};
    executeSQL(__PRETTY_FUNCTION__, DB, sql, getStatus, ptrCurrentStatus);

    std::string newStatus{};
    currentStatus ? newStatus = "0" : newStatus = "1";
    sql = "UPDATE REMINDERS SET ENABLE = ";
    sql.append(newStatus)
        .append(" WHERE ID = ")
        .append(std::to_string(idAndTimeRange.first))
        .append(";");

    if (std::stoi(newStatus)) {
        updateNextNotification(DB, idAndTimeRange.first, idAndTimeRange.second);
    }

    executeSQL(__PRETTY_FUNCTION__, DB, sql);
}

void disableAll(sqlite3 *DB) {
    // if the first reminder is enabeled, disable all. And vice-versa
    std::string sql{"SELECT ENABLE FROM REMINDERS LIMIT 1;"};
    int currentStatus{0};
    int *ptrCurrentStatus{&currentStatus};
    executeSQL(__PRETTY_FUNCTION__, DB, sql, getStatus, ptrCurrentStatus);

    std::string newStatus{};
    currentStatus ? newStatus = "0" : newStatus = "1";
    sql = "UPDATE REMINDERS SET ENABLE='";
    sql.append(newStatus).append("';");

    if (std::stoi(newStatus)) {
        for (const auto &id : g_idAndTimeRangeList) {
            updateNextNotification(DB, id.first, id.second);
        }
    }

    executeSQL(__PRETTY_FUNCTION__, DB, sql);
}

void changeText(sqlite3 *DB, int id) {
    std::cout << "Write new text: ";
    std::string newText{};
    std::getline(std::cin >> std::ws, newText);

    std::string sql{"UPDATE REMINDERS SET REMINDER = '"};
    sql.append(newText)
        .append("' ")
        .append("WHERE ID = ")
        .append(std::to_string(id))
        .append(";");

    executeSQL(__PRETTY_FUNCTION__, DB, sql);

    std::cout << "New text accepted.\n";
}

std::int32_t convertUserInputTime(std::string &str) {
    int days{};
    int hours{};
    int minutes{};
    char delimeter{};

    // Erase all whitespaces to properly check for correctness
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    // Check for the right format
    if (str.size() != 9)
        return -1;
    if (std::tolower(str[2]) != 'd' || std::tolower(str[5]) != 'h' ||
        std::tolower(str[8]) != 'm')
        return -1;

    std::stringstream ss{str};
    ss >> days >> delimeter >> hours >> delimeter >> minutes;

    return days * 1440 + hours * 60 + minutes;
}

void changeTime(sqlite3 *DB, std::pair<int, std::int32_t> &idAndTimeRange) {
    std::int32_t newTime{};

    while (true) {
        std::cout << "Write new time using format 00d00h00m (e.g. 01d00h23m): ";
        std::string newTimeString{};
        std::getline(std::cin >> std::ws, newTimeString);

        newTime = convertUserInputTime(newTimeString);

        if (newTime == -1) {
            std::cout << "Incorrect input. Try again.\n";
            continue;
        }
        break;
    }

    std::string sql{"UPDATE REMINDERS SET TIME_RANGE = "};
    sql.append(std::to_string(newTime))
        .append(" WHERE ID = ")
        .append(std::to_string(idAndTimeRange.first))
        .append(";");

    executeSQL(__PRETTY_FUNCTION__, DB, sql);

    idAndTimeRange.second = newTime;
    updateNextNotification(DB, idAndTimeRange.first, idAndTimeRange.second);

    std::cout << "New time accepted.\n";
}

void deleteReminder(sqlite3 *DB, int id) {
    std::string sql{"DELETE FROM REMINDERS WHERE ID = "};
    sql.append(std::to_string(id)).append(";");

    executeSQL(__PRETTY_FUNCTION__, DB, sql);

    std::cout << "The reminder deleted.\n";
}

void updateNextNotification(sqlite3 *DB, int id, std::int32_t timeRange) {
    std::int64_t timeNow =
        std::chrono::duration_cast<std::chrono::minutes>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();

    std::int64_t newNextNotification{Random::get(1, timeRange) + timeNow};

    std::string sql = {"UPDATE REMINDERS SET NEXT_NOTIFICATION = '"};
    sql.append(std::to_string(newNextNotification))
        .append("' ")
        .append("WHERE ID = ")
        .append(std::to_string(id))
        .append(";");

    executeSQL(__PRETTY_FUNCTION__, DB, sql, 0, nullptr);
}
