#include "weeklyGoals.h"
#include <iostream>
#include <fstream>

void WeeklyGoals::addGoal(const std::string& goal) {
    goals.push_back(goal);
}

void WeeklyGoals::viewGoals() const {
    std::cout << "\n--- Weekly Goals ---\n";
    for (size_t i = 0; i < goals.size(); ++i) {
        std::cout << (i + 1) << ". " << goals[i] << "\n";
    }
}

void WeeklyGoals::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    for (const auto& goal : goals) {
        file << goal << "\n";
    }
}

void WeeklyGoals::loadFromFile(const std::string& filename) {
    goals.clear();
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        goals.push_back(line);
    }
}
