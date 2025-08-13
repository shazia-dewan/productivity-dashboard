#ifndef WEEKLYGOALS_H
#define WEEKLYGOALS_H

#include <vector>
#include <string>
#include <map>


class WeeklyGoals {
private:
    std::map<std::string, int> goals;

public:
    void addGoal(const std::string& goal, int frequency);
    void deleteGoal(const std::string& goal);
    void viewGoals() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif
