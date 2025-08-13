#include <iostream>
#include <string>
#include "schedule.h"
#include "habitTracker.h"
#include "weeklyGoals.h"
#include <fstream>
#include <ctime>
#include <filesystem>

namespace fs = std::filesystem;

//Checks if it is sunday if so all weekly goals are reset
void resetWeeklyFiles() {
    // Get current day of week (0 = Sunday, 6 = Saturday)
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    int dayOfWeek = now->tm_wday;

    if (dayOfWeek == 0) {  // Sunday
        std::string parentDir = "../";  // Adjust if needed
        std::string goalsPath = parentDir + "goals.txt";
        std::string habitsPath = parentDir + "habits.txt";

        // Clear goals.txt
        std::ofstream goalsFile(goalsPath, std::ios::trunc);
        if (goalsFile) {
            std::cout << "goals.txt reset.\n";
        } else {
            std::cerr << "Failed to reset goals.txt\n";
        }

        // Clear habits.txt
        std::ofstream habitsFile(habitsPath, std::ios::trunc);
        if (habitsFile) {
            std::cout << "habits.txt reset.\n";
        } else {
            std::cerr << "Failed to reset habits.txt\n";
        }
    } else {
        std::cout << " Not Sunday. No reset performed.\n";
    }
}


void scheduleMenu(Schedule& mySchedule, int startHour, int endHour) {
    int choice, hour;
    std::string desc;

    while (true) {
        std::cout << "\033[1;32m+------------------------+\033[0m\n";
        std::cout << "\033[1;32m|      Daily Schedule     |\033[0m\n";
        std::cout << "\033[1;32m+------------------------+\033[0m\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. View Schedule\n";
        std::cout << "3. Clear Schedule\n";
        std::cout << "4. Back\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore();

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
            mySchedule.clearSchedule();
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }
}


void habitMenu(HabitTracker& tracker) {
    int choice;
    while (true) {
        std::cout << "\033[35m+------------------------+\033[0m\n";
        std::cout << "\033[35m|      Habit Tracker      |\033[0m\n";
        std::cout << "\033[35m+------------------------+\033[0m\n";
        std::cout << "1. View Habits\n";
        std::cout << "2. Add Habit\n";
        std::cout << "3. Update Habit\n";
        std::cout << "4. Delete Habit\n";
        std::cout << "5. Back\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            tracker.viewHabits();
        } else if (choice == 2) {
            std::string habit;
            std::cout << "Enter new habit name: ";
            std::getline(std::cin, habit);
            tracker.addHabit(habit);
        } else if (choice == 3) {
            std::string habit;
            int count;
            std::cout << "Enter habit name: ";
            std::getline(std::cin, habit);
            std::cout << "Enter how many times you did it today: ";
            std::cin >> count;
            std::cin.ignore();
            tracker.updateHabit(habit, count);
        } else if (choice == 4) {
            std::string habit;
            std::cout << "Enter habit name to delete: ";
            std::getline(std::cin, habit);
            tracker.deleteHabit(habit);
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }
}


void weeklyMenu(WeeklyGoals& weeklyGoals) {
    int choice;
    while (true) {
        std::cout << "\033[1;34m+------------------------+\033[0m\n";
        std::cout << "\033[1;34m|       Weekly Goals      |\033[0m\n";
        std::cout << "\033[1;34m+------------------------+\033[0m\n";
        std::cout << "1. View Goals\n";
        std::cout << "2. Add Goal\n";
        std::cout << "3. Delete Goal\n";
        std::cout << "4. Back\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            weeklyGoals.viewGoals();
        } else if (choice == 2) {
            std::string goal;
            int freq;
            std::cout << "Enter new weekly goal: ";
            std::getline(std::cin, goal);
            std::cout << "How many times per week do you want to achieve this? ";
            std::cin >> freq;
            std::cin.ignore();
            weeklyGoals.addGoal(goal, freq);
        } else if (choice == 3) {
            std::string goalToDelete;
            std::cout << "Enter the goal to delete: ";
            std::getline(std::cin, goalToDelete);
            weeklyGoals.deleteGoal(goalToDelete);
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }
}



int main() {

    const int startHour = 8;
    const int endHour = 20;

    Schedule mySchedule(startHour, endHour);
    mySchedule.loadFromFile("tasks.txt");

    HabitTracker tracker;
    tracker.loadFromFile("habits.txt");

    WeeklyGoals weeklyGoals;
    weeklyGoals.loadFromFile("goals.txt");

    int choice;

    resetWeeklyFiles(); // Only if its sunday

    while (true) {

        std::cout << "\033[1;34m\n=============================\n";
        std::cout << "     📅 Productivity Hub     \n";
        std::cout << "=============================\033[0m\n";
        std::cout << "\033[1;33m1.\033[0m Daily Schedule 🗓️\n";
        std::cout << "\033[1;33m2.\033[0m Habit Tracker ✅\n";
        std::cout << "\033[1;33m3.\033[0m Weekly Goals 🎯\n";
        std::cout << "\033[1;33m4.\033[0m Save & Exit 💾\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            scheduleMenu(mySchedule, startHour, endHour); 
        } else if (choice == 2) {
            habitMenu(tracker);
        } else if (choice == 3) {
            weeklyMenu(weeklyGoals);
        } else if (choice == 4) {
            mySchedule.saveToFile("tasks.txt");
            tracker.saveToFile("habits.txt");
            weeklyGoals.saveToFile("goals.txt");
            std::cout << "All data saved. Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid option. Try again.\n";
        }
    }

}

