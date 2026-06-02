#include "Student.h"

Student::Student(const std::string& username, const std::string& password) : User(username, password, Role::Student),
	  completedTasks(0), inProgressTasks(0), performanceScore(0.0) { }

std::unique_ptr<User> Student::clone() const
{
	return std::make_unique<Student>(*this);
}

int Student::getCompletedTasks() const
{
	return completedTasks;
}

int Student::getInProgressTasks() const
{
	return inProgressTasks;
}

double Student::getPerformanceScore() const
{
	return performanceScore;
}

void Student::incrementCompletedTasks()
{
	completedTasks++;
}

void Student::incrementInProgressTasks()
{
	inProgressTasks++;
}

void Student::decrementInProgressTasks()
{
	if (inProgressTasks > 0)
	{
		inProgressTasks--;
	}
}

void Student::addPerformancePoints(double points)
{
	performanceScore += points;
}

void Student::displayInfo(std::ostream& os) const
{
	User::displayInfo(os);
	os << "Completed tasks: " << completedTasks << "\n"
		<< "In progress: " << inProgressTasks << "\n"
		<< "Performance score: " << performanceScore << "\n";
}