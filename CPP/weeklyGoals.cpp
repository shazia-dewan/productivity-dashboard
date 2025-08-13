#include "weeklyGoals.h"
#include <iostream>
#include <fstream>

void WeeklyGoals::addGoal(const std::string& goal, int frequency) {
    goals[goal] = frequency;
}


void WeeklyGoals::viewGoals() const {
    std::cout << "\n--- Weekly Goals ---\n";
    if (goals.empty()) {
        std::cout << "No goals set yet.\n";
    } else {
        for (const auto& [goal, freq] : goals) {
            std::cout << "- " << goal << ": " << freq << "x/week\n";
        }
    }
}

void WeeklyGoals::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    for (const auto& [goal, freq] : goals) {
        file << goal << "|" << freq << "\n";
    }
}

void WeeklyGoals::loadFromFile(const std::string& filename) {
    goals.clear();
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        auto delimPos = line.find('|');
        if (delimPos != std::string::npos) {
            std::string goal = line.substr(0, delimPos);
            int freq = std::stoi(line.substr(delimPos + 1));
            goals[goal] = freq;
        }
    }
}

void WeeklyGoals::deleteGoal(const std::string& goal){
    if (goals.erase(goal)) {
        std::cout << "Goal \"" << goal << "\" deleted.\n";
    }
    else {
        std::cout << "Goal not found.\n";
    }
}

