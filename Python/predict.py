# Gives predictions on each goal for the current date
import pandas as pd
import json
import joblib
from datetime import datetime, timedelta

# Load model
model = joblib.load("habit_model.pkl")

# Load weekly goals
with open("weekly_goals.json") as f:
    weekly_goals = json.load(f)

# Load log
habit_log = pd.read_csv("habit_log.csv", parse_dates=["Date"])

# Week start
today = datetime.today().date()
week_start = today - timedelta(days=today.weekday())
day_of_week = today.weekday()
days_left = 6 - day_of_week

# Filter this week
week_data = habit_log[habit_log["Date"].dt.date >= week_start]
week_totals = week_data.groupby("Habit")["TimesCompleted"].sum().reset_index()

print(f"Predictions for {today}:\n")

for habit, goal in weekly_goals.items():
    times_done = week_totals.loc[week_totals["Habit"] == habit, "TimesCompleted"].sum()
    progress_ratio = min(times_done / goal, 1)
    avg_daily_rate_needed = (goal - times_done) / max(days_left, 1)
    momentum = times_done / (7 - days_left)

    X = pd.DataFrame([{
        "TimesCompleted": times_done,
        "WeeklyGoal": goal,
        "DaysLeft": days_left,
        "ProgressRatio": progress_ratio,
        "AvgDailyRateNeeded": avg_daily_rate_needed,
        "Momentum": momentum
    }])

    prob = model.predict_proba(X)[0][1] * 100
    status = "✅ On track" if prob >= 50 else ("⚠️ At risk" if prob >= 30 else "❌ Off track")

    if times_done >= goal:
        print(f"- {habit}: ✅ Goal already met ({times_done}/{goal})")
    else:
        print(f"- {habit}: {status} ({times_done}/{goal}) – {prob:.1f}% likelihood")










