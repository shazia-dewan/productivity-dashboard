# This file read our daily habits and aggregates it to make a new csv with our weekly progress
# It also generates graphs to visualize our progress of habits
import pandas as pd
import matplotlib.pyplot as plt
import json
from datetime import datetime
import os

# --- Step 1: Ensure weekly_goals.json exists ---
current_dir = os.path.dirname(__file__)
parent_dir = os.path.abspath(os.path.join(current_dir, "../CPP"))
goals_txt_path = os.path.join(parent_dir, "goals.txt")
goals_json_path = os.path.join(current_dir, "weekly_goals.json")

# Create weekly_goals.json from goals.txt if needed
if not os.path.exists(goals_json_path):
    goals = {}
    try:
        with open(goals_txt_path, "r") as f:
            for line in f:
                line = line.strip()
                if not line or "|" not in line:
                    continue
                habit, freq = line.split("|", 1)
                habit = habit.strip()
                try:
                    goals[habit] = int(freq.strip())
                except ValueError:
                    print(f"Skipping invalid frequency for habit: {habit}")
    except FileNotFoundError:
        print(f"goals.txt not found at {goals_txt_path}")
        exit(1)

    with open(goals_json_path, "w") as f:
        json.dump(goals, f, indent=4)
    print(f"Created weekly_goals.json with {len(goals)} goals.")

# Load habit log 
df = pd.read_csv('habit_log.csv')
df['Date'] = pd.to_datetime(df['Date'])

# Load weekly goals
with open(goals_json_path) as f:
    weekly_goals = json.load(f)

# Add week number and year 
df['Week'] = df['Date'].dt.isocalendar().week
df['Year'] = df['Date'].dt.isocalendar().year

# Group by Year, Week, Habit
weekly_summary = df.groupby(['Year', 'Week', 'Habit'])['TimesCompleted'].sum().reset_index()

# Add Goal & Completion Status 
def get_goal(habit):
    return weekly_goals.get(habit, 0)  # default to 0 if no goal is defined

weekly_summary['WeeklyGoal'] = weekly_summary['Habit'].apply(get_goal)
weekly_summary['CompletedGoal'] = (weekly_summary['TimesCompleted'] >= weekly_summary['WeeklyGoal']).astype(int)

# Save weekly summary to CSV 
weekly_summary.to_csv('weekly_summary.csv', index=False)

# Visualize progress over time 
pivot_plot = df.groupby(['Date', 'Habit'])['TimesCompleted'].sum().unstack().fillna(0)

pivot_plot.plot(kind='line', marker='o', figsize=(10, 6))
plt.title('Habit Completion Over Time')
plt.xlabel('Date')
plt.ylabel('Times Completed')
plt.grid(True)
plt.tight_layout()
plt.legend(title='Habits')
plt.show()

