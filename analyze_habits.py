import pandas as pd
import matplotlib.pyplot as plt

# Load the habit log CSV
df = pd.read_csv('habit_log.csv')

# Group data by Date and Habit
grouped = df.groupby(['Date', 'Habit']).sum().reset_index()

# Pivot the table: Dates as rows, Habits as columns
pivot_table = grouped.pivot(index='Date', columns='Habit', values='TimesCompleted').fillna(0)

# Plot line graph
pivot_table.plot(kind='line', marker='o', figsize=(10,6))

plt.title('Habit Completion Over Time')
plt.xlabel('Date')
plt.ylabel('Times Completed')
plt.grid(True)
plt.tight_layout()
plt.legend(title='Habits')
plt.show()
