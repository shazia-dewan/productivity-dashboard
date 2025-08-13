# This generates the dataset that we will use to train the model (ony needs to be executed once)
import pandas as pd
from datetime import datetime, timedelta
import json


# Load your habit log and weekly goals
habit_log = pd.read_csv('habit_log.csv')
with open('weekly_goals.json', 'r') as f:
    weekly_goals = json.load(f)

# Add year and ISO week number to log
habit_log['Date'] = pd.to_datetime(habit_log['Date'])
habit_log['Year'] = habit_log['Date'].dt.isocalendar().year
habit_log['Week'] = habit_log['Date'].dt.isocalendar().week
habit_log['DayOfWeek'] = habit_log['Date'].dt.day_name()

# Aggregate completions
habit_log['CumulativeCompleted'] = 0
daily_features = []

# Get all unique combinations of week and habit
for (year, week, habit), group in habit_log.groupby(['Year', 'Week', 'Habit']):
    # Get weekly goal
    weekly_goal = weekly_goals.get(habit, 0)

    # Create daily rows with running total
    group = group.sort_values('Date')
    running_total = 0
    end_of_week = group['Date'].max().to_period('W').end_time.date()

    for idx, row in group.iterrows():
        running_total += row['TimesCompleted']
        days_left = (end_of_week - row['Date'].date()).days

        completed_goal = int(running_total >= weekly_goal)

        daily_features.append({
            'Date': row['Date'].date(),
            'Year': year,
            'Week': week,
            'DayOfWeek': row['DayOfWeek'],
            'Habit': habit,
            'CumulativeCompleted': running_total,
            'WeeklyGoal': weekly_goal,
            'DaysLeft': days_left,
            'CompletedGoal': completed_goal
        })

# Create DataFrame
daily_df = pd.DataFrame(daily_features)
daily_df.to_csv('daily_features.csv', index=False)
print("daily_features.csv generated.")
