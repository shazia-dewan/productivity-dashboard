# Habit Tracking Dashboard

## Summary
The **Habit Tracking Dashboard** is a hybrid **C++ and Python** project designed to help you monitor, manage, and predict your progress toward personal goals.

- The **C++ dashboard** provides a console-based interface for tracking habits, setting weekly goals, and managing your daily schedule.
- The **Python scripts** analyze your progress, generate features for machine learning, and predict the likelihood of completing your weekly goals.

This project combines habit tracking, data analysis, and predictive modeling into one system.

---

## 🛠 Tech Stack

### Languages
- **C++** – Console dashboard and habit management
- **Python 3.x** – Data processing and machine learning

### Python Libraries
- `pandas` – Data handling
- `matplotlib` – Graphing progress
- `scikit-learn` – Machine learning
- `joblib` – Model saving/loading

---

## 📂 Directory Structure

project/

- CPP/  
   - main.cpp 
   - makefile  
   - schedule.cpp
   - schedule.h
   - habitTracker.cpp
   - habitTracker.h
   - weeklyGoals.cpp
   - weeklyGoals.h
     
- Python/  
   - analyze_habits.py  
   -  generate_daily_features.py  
   -  predict.py  
   -  train_model.py
     
- requirements.txt  
- README.md  


---

##  Setup Instructions

### 1️ Create and Activate a Virtual Environment

```bash
# Create virtual environment
python3 -m venv venv  

# Activate (Mac/Linux)
source venv/bin/activate  

# Activate (Windows PowerShell)
venv\Scripts\Activate

```

### 2 Install Required Libraries
Make sure your virtual environment is activated, then run:

```bash
pip install -r requirements.txt
```

### 3 Running the C++ Dashboard
```bash
# Navigate to the C++ directory
cd cpp
# Compile the dashboard
make
# Run the dashboard
./dashboard
```

### 4 Running the Python Scripts
```bash
# Visualize Your Progress
# See habit trends and statistics in graph form.
python python/analyze_habits.py

# Generate Daily Features (Run Once)
# This creates or updates your daily_features.csv file.
python python/generate_daily_features.py

# Train the Machine Learning Model
python python/train_model.py

# Predict Today’s Goal Completion Likelihood
# This uses the trained model to predict if you will complete your weekly goal.
python python/predict.py

```

### Future Ideas
- Add unit tests (ex google tests)
- Add containerization such as Docker
