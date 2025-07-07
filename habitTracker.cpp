#include "habitTracker.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <sys/stat.h>

bool fileExists(const std::string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}


std::string getCurrentDate() {
    time_t t = time(nullptr);
    tm* timePtr = localtime(&t);

    char buffer[11];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d",
             timePtr->tm_year + 1900,
             timePtr->tm_mon + 1,
             timePtr->tm_mday);

    return std::string(buffer);
}


void HabitTracker::addHabit(const std::string& habit) {
    habits[habit] = 0;
}

void HabitTracker::updateHabit(const std::string& habit, int count) {
    habits[habit] += count;
    std::cout << "Habit \"" << habit << "\" updated by " << count << ".\n";

    std::ofstream logFile;
    bool exists = fileExists("habit_log.csv");
    logFile.open("habit_log.csv", std::ios::app);

    if (!exists) {
        logFile << "Date,Habit,TimesCompleted\n";
    }

    logFile << getCurrentDate() << "," << habit << "," << count << "\n";
    logFile.close();
}


void HabitTracker::viewHabits() const {
    std::cout << "\n--- Habit Tracker ---\n";
    for (const auto& [habit, count] : habits) {
        std::cout << habit << ": " << count << "\n";
    }
}

void HabitTracker::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    for (const auto& [habit, count] : habits) {
        file << habit << " " << count << "\n";
    }
}

void HabitTracker::loadFromFile(const std::string& filename) {
    habits.clear();
    std::ifstream file(filename);
    std::string habit;
    int count;
    while (file >> habit >> count) {
        habits[habit] = count;
    }
}

void HabitTracker::deleteHabit(const std::string& habit) {
    if (habits.erase(habit)) {
        std::cout << "Habit \"" << habit << "\" deleted.\n";
    } else {
        std::cout << "Habit not found.\n";
    }
}

