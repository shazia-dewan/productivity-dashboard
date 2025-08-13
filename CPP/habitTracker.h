#ifndef HABITTRACKER_H
#define HABITTRACKER_H

#include <map>
#include <string>

class HabitTracker {
private:
    std::map<std::string, int> habits; // habit -> count

public:
    void addHabit(const std::string& habit);
    void updateHabit(const std::string& habit, int count);
    void viewHabits() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    void deleteHabit(const std::string& habit);
};

#endif
