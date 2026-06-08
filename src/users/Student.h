#pragma once
#include "User.h"
#include <vector>
#include <string>

class Student : public User
{
	int completedTasks;
	int inProgressTasks;
	double performanceScore;
	std::vector<std::string> tags;

public:
	Student(const std::string& username, const std::string& password);

	std::unique_ptr<User> clone() const override;

	int getCompletedTasks() const;
	int getInProgressTasks() const;
	double getPerformanceScore() const;

	void incrementCompletedTasks();
	void incrementInProgressTasks();
	void decrementInProgressTasks();
	
	void addPerformancePoints(double points);

	void displayInfo(std::ostream& os) const override;

	void save(std::ostream& os) const override;
	void loadSubclass(std::istream& is) override;
};

