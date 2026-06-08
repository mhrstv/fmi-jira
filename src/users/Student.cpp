#include "Student.h"
#include "../exceptions/ValidationException.h"
#include "../utils/DataStream.h"

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
		<< "  Performance Score: " << performanceScore << "\n";
}

void Student::save(std::ostream& os) const
{
	User::save(os);
	DataStream::writeInt(os, completedTasks);
	DataStream::writeInt(os, inProgressTasks);
	DataStream::writeDouble(os, performanceScore);
	
	DataStream::writeSizeT(os, tags.size());
	for (const auto& tag : tags)
	{
		DataStream::writeString(os, tag);
	}
}

void Student::loadSubclass(std::istream& is)
{
	completedTasks = DataStream::readInt(is);
	inProgressTasks = DataStream::readInt(is);
	performanceScore = DataStream::readDouble(is);

	size_t numTags = DataStream::readSizeT(is);
	tags.clear();
	for (size_t i = 0; i < numTags; ++i)
	{
		tags.push_back(DataStream::readString(is));
	}
}