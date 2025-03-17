//
//  Settings.cpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 14.03.25.
//

#include "Settings.hpp"
#include "Constants.hpp"
#include "Print.hpp"

void cleanInputStream();

void addReminder(std::vector<Reminders>& listReminders)
{
    std::cout << Constants::linesVisualDivider;
    std::cout << "Write your reminder: ";
    std::string reminder {};
    std::getline(std::cin >> std::ws, reminder);
    
    listReminders.push_back( Reminders { reminder });
    
}

void disableSingleReminder(Reminders& reminder){
    reminder.getStatus() ? reminder.setStatus(false) : reminder.setStatus(true);
}

void disableAll(std::vector<Reminders>& listReminders)
{
    //if the first reminder is enabeled, disable all. And vice-versa
    bool currentStatus { listReminders[0].getStatus() };
    
    for (auto& r : listReminders)
        currentStatus ? r.setStatus(false) : r.setStatus(true);
}

void changeText(Reminders& reminder)
{
    std::cout << Constants::linesVisualDivider;
    std::cout << "Write new text: ";
    std::string newText {};
    std::getline(std::cin >> std::ws, newText);
    
    reminder.setRemind(newText);
    
    std::cout << "New text accepted.\n";
}

std::int32_t convertUserInputTime(std::string& str)
{
    int days {};
    int hours {};
    int minutes {};
    char delimeter {};
    
    //Erase all whitespaces to properly check for correctness
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    
    //Check for the right format
    if (std::tolower(str[2]) != 'd' || std::tolower(str[5]) != 'h'
        || std::tolower(str[8]) != 'm' || str.size() != 9)
        return -1;
    
    std::stringstream ss { str };
    ss >> days >> delimeter >> hours >> delimeter >> minutes;
    
    return days * 1440 + hours * 60 + minutes;
}

void changeTime(Reminders& reminder)
{
    std::int32_t newTime {};
    
    while (true)
    {
        std::cout << Constants::linesVisualDivider;
        std::cout << "Write new time using format 00d00h00m (e.g. 01d00h23m): ";
        std::string newTimeString {};
        std::getline(std::cin >> std::ws, newTimeString);
        
        newTime = convertUserInputTime(newTimeString);
        
        if (newTime == -1)
            {
                std::cout << "Incorrect input. Try again.\n";
                continue;
            }
        break;
    }
    
    
    reminder.setMaxTimeSchedule(newTime);
    
    std::cout << "New time accepted.\n";
}

void deleteReminder(std::vector<Reminders>& listReminders, std::size_t indexDelete)
{
    listReminders
        .erase(listReminders.begin() + static_cast<std::ptrdiff_t>(indexDelete));
    
    std::cout << "The reminder deleted.\n";
}

void settings(std::vector<Reminders>& listReminders)
{
    std::cout << Constants::linesVisualDivider;
    printRemindersList(listReminders);
    std::size_t reminderIndex {};
    
    while(true)
    {
        std::cout << "Which reminder would you like to change? (0 to exit): ";
        std::cin >> reminderIndex;
        
        if(!std::cin)
        {
            cleanInputStream();
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }
    
    if (reminderIndex <= 0)
        return;
    
    if (reminderIndex > listReminders.size())
    {
        std::cout << "There is no reminder.\n";
        return;
    }
    
    //Adjustment for correct indexing in vector
    --reminderIndex;
    
    while(true)
    {
        std::cout << Constants::linesVisualDivider;
        std::cout << "The reminder to change:\n";
        printSingleReminder(listReminders[reminderIndex]);
        
        std::cout << "1 - Disable/Enable Notification\n";
        std::cout << "2 - Change Text\n";
        std::cout << "3 - Change Time\n";
        std::cout << "4 - Delete\n";
        std::cout << "0 - Back\n";
        
        std::cout << "Enter a number to proceed: ";
        int choice {};
        std::cin >> choice;
        
        if(!std::cin)
        {
            cleanInputStream();
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                disableSingleReminder(listReminders[reminderIndex]);
                break;
            case 2:
                changeText(listReminders[reminderIndex]);
                break;
            case 3:
                changeTime(listReminders[reminderIndex]);
                break;
            case 4:
                deleteReminder(listReminders, reminderIndex);
                return;
            case 0:
                return;
                
            default:
                std::cout << "Incorrect. Try again.\n";
                continue;
        }
    }
    
}
