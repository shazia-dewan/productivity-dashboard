#include <iostream>
#include "schedule.h"

int main() {
    int startHour, endHour;

    std::cout << "Enter your workday start hour (e.g., 8): ";
    std::cin >> startHour;
    std::cout << "Enter your workday end hour (e.g., 20): ";
    std::cin >> endHour;

    Schedule mySchedule(startHour, endHour);
    mySchedule.loadFromFile("tasks.txt");

    int choice, hour;
    std::string desc;

    while (true) {
        std::cout << "\n1. Add Task\n2. View Schedule\n3. Save & Exit\nEnter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Enter hour (" << startHour << " to " << endHour << "): ";
            std::cin >> hour;
            std::cin.ignore();
            std::cout << "Enter task description: ";
            std::getline(std::cin, desc);
            mySchedule.addTask(hour, desc);
        } else if (choice == 2) {
            mySchedule.displaySchedule();
        } else if (choice == 3) {
            mySchedule.saveToFile("tasks.txt");
            std::cout << "Saved. Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}

