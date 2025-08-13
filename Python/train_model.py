# This file trains the model using RandomForestClassifier
import pandas as pd
import joblib
import json
from sklearn.ensemble import RandomForestClassifier

# Load historical log
df = pd.read_csv("habit_log.csv", parse_dates=["Date"])

# Load weekly goals from JSON
with open("weekly_goals.json") as f:
    weekly_goals = json.load(f)

# Add week/year columns
df["Week"] = df["Date"].dt.isocalendar().week
df["Year"] = df["Date"].dt.year

# --- Create training rows for partial weeks ---
training_rows = []
for (year, week, habit), group in df.groupby(["Year", "Week", "Habit"]):
    if habit not in weekly_goals:
        continue  # Skip habits not in goals

    goal = weekly_goals[habit]
    full_week_total = group["TimesCompleted"].sum()
    final_goal_met = int(full_week_total >= goal)

    for day in group["Date"].dt.date.unique():
        day_num = pd.Timestamp(day).weekday()  # Monday=0
        days_left = 6 - day_num
        times_so_far = group[group["Date"].dt.date <= day]["TimesCompleted"].sum()
        progress_ratio = min(times_so_far / goal, 1)
        avg_daily_rate_needed = (goal - times_so_far) / max(days_left, 1)
        momentum = times_so_far / (7 - days_left)

        training_rows.append({
            "Year": year,
            "Week": week,
            "TimesCompleted": times_so_far,
            "WeeklyGoal": goal,
            "DaysLeft": days_left,
            "ProgressRatio": progress_ratio,
            "AvgDailyRateNeeded": avg_daily_rate_needed,
            "Momentum": momentum,
            "GoalMet": final_goal_met
        })

training_df = pd.DataFrame(training_rows)

# Train model
X = training_df[["TimesCompleted", "WeeklyGoal", "DaysLeft", "ProgressRatio", "AvgDailyRateNeeded", "Momentum"]]
y = training_df["GoalMet"]

model = RandomForestClassifier(n_estimators=200, random_state=42)
model.fit(X, y)

# Save
joblib.dump(model, "habit_model.pkl")
print("Model trained and saved.")




