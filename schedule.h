#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>
#include <vector>

class Schedule {
private:
    int startHour;
    int endHour;
    std::vector<std::string> hourlyTasks;

public:
    Schedule(int start = 8, int end = 20); // Default 8 AM - 8 PM
    void addTask(int hour, const std::string& description);
    void displaySchedule() const;
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
    bool isHourInRange(int hour) const;
};

#endif


