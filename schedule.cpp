#include "schedule.h"
#include <iostream>
#include <fstream>

Schedule::Schedule(int start, int end) : startHour(start), endHour(end) {
    if (startHour < 0) startHour = 0;
    if (endHour > 23) endHour = 23;
    hourlyTasks.resize(24, "Free");
}

bool Schedule::isHourInRange(int hour) const {
    return hour >= startHour && hour <= endHour;
}

void Schedule::addTask(int hour, const std::string& description) {
    if (isHourInRange(hour)) {
        hourlyTasks[hour] = description;
    } else {
        std::cout << "That hour is outside your workday (" << startHour << ":00 - " << endHour << ":00).\n";
    }
}

void Schedule::displaySchedule() const {
    std::cout << "\n--- Daily Schedule (" << startHour << ":00 - " << endHour << ":00) ---\n";
    for (int i = startHour; i <= endHour; ++i) {
        std::cout << i << ":00 - " << hourlyTasks[i] << "\n";
    }
}

void Schedule::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file) {
        for (int i = 0; i < 24 && file; ++i) {
            std::getline(file, hourlyTasks[i]);
        }
    }
}

void Schedule::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    for (const auto& task : hourlyTasks) {
        file << task << "\n";
    }
}

void Schedule::clearSchedule() {
    for (int i = startHour; i <= endHour; ++i) {
        hourlyTasks[i] = "free";
    }
    std::cout << "Schedule cleared.\n";
}



