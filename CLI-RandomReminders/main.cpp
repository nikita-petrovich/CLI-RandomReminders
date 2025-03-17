//
//  main.cpp
//  CLI-RandomReminders
//
//  Created by Nikita Petrovich on 13.03.25.
//

#include "Reminders.hpp"
#include "Settings.hpp"
#include "Constants.hpp"
#include "Spelling.hpp"
#include "Print.hpp"
#include <iostream>
#include <vector>
#include <numeric>

void cleanInputStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input. Try again.\n";
}


void mainMenu(std::vector<Reminders>& listReminders)
{
    while (true)
    {
        std::cout << Constants::linesVisualDivider;
        std::cout << "Your reminders:\n";
        printRemindersList(listReminders);
        std::cout << "Main Menu:\n";
        std::cout << "1 - Add new reminder\n";
        std::cout << "2 - Settings\n";
        std::cout << "3 - Disable/Enable all\n";
        std::cout << "0 - Exit\n";
        
        while (true)
        {
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
                    addReminder(listReminders);
                    break;
                case 2:
                    settings(listReminders);
                    break;
                case 3:
                    disableAll(listReminders);
                    break;
                case 0:
                    std::cout << "Are you sure? You won't be able to recieve reminders (1 - YES; 0 - NO): ";
                    std::cin >> choice;
                    if(!std::cin)
                    {
                        cleanInputStream();
                        continue;
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if (choice == 1)
                        return;
                    else if (choice == 0)
                        break;
                    
                    std::cout << "Incorrect. Try again.\n";
                    break;
                    
                    
                default:
                    std::cout << "Incorrect. Try again.\n";
                    continue;
            }
            break;
        }
    }
    
}

int main() {
    
    std::vector<Reminders> listReminders { Reminders { "Does this bring you closer to your dream?" } };
    
    mainMenu(listReminders);
    
    spellReminders(listReminders);
    
    return 0;
}
