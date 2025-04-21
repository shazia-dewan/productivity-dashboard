#ifndef WEEKLYGOALS_H
#define WEEKLYGOALS_H

#include <vector>
#include <string>

class WeeklyGoals {
private:
    std::vector<std::string> goals;

public:
    void addGoal(const std::string& goal);
    void viewGoals() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif
