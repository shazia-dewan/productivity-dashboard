#include "habitTracker.h"
#include <iostream>
#include <fstream>

void HabitTracker::addHabit(const std::string& habit) {
    habits[habit] = 0;
}

void HabitTracker::updateHabit(const std::string& habit, int count) {
    if (habits.count(habit)) {
        habits[habit] += count;
    } else {
        std::cout << "Habit not found.\n";
    }
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

