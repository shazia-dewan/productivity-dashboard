all: dashboard

dashboard: main.cpp schedule.cpp habitTracker.cpp weeklyGoals.cpp 
	g++ -std=c++17 -o dashboard main.cpp schedule.cpp habitTracker.cpp weeklyGoals.cpp -lpthread

clean:
	rm -f dashboard
