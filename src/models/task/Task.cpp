#include "Task.h"
#include "../../users/User.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/StateException.h"

size_t Task::idGen = 100;

Task::Task(const std::string& title, const std::string& description, TaskType type, TaskPriority priority)
	: id(++idGen), title(title), description(description), type(type), priority(priority),
	  status(TaskStatus::ToDo), assignee(nullptr), deadline(), points(0), grade(0.0), approved(false)
{
	if (title.empty())
	{
		throw ValidationException("Task title cannot be empty.");
	}
	if (description.empty())
	{
		throw ValidationException("Task description cannot be empty.");
	}
	changeHistory.emplace_back(nullptr, "task", "", "created " + getFormattedId(), Date());
}

size_t Task::getId() const
{
	return id;
}

std::string Task::getFormattedId() const
{
	return "FMI-" + std::to_string(id);
}

const std::string& Task::getTitle() const
{
	return title;
}

const std::string& Task::getDescription() const
{
	return description;
}

TaskType Task::getType() const
{
	return type;
}

TaskPriority Task::getPriority() const
{
	return priority;
}

TaskStatus Task::getStatus() const
{
	return status;
}

const User* Task::getAssignee() const
{
	return assignee;
}

const Date& Task::getDeadline() const
{
	return deadline;
}

int Task::getPoints() const
{
	return points;
}

double Task::getGrade() const
{
	return grade;
}

bool Task::isApproved() const
{
	return approved;
}

const std::vector<Comment>& Task::getComments() const
{
	return comments;
}

const std::vector<std::string>& Task::getTags() const
{
	return tags;
}

const std::vector<HistoryEntry>& Task::getChangeHistory() const
{
	return changeHistory;
}

void Task::setTitle(const std::string& title, const User* changedBy, const Date& timestamp)
{
	if (title.empty())
	{
		throw ValidationException("Task title cannot be empty.");
	}
	changeHistory.emplace_back(changedBy, "title", this->title, title, timestamp);
	this->title = title;
}

void Task::setDescription(const std::string& description, const User* changedBy, const Date& timestamp)
{
	if (description.empty())
	{
		throw ValidationException("Task description cannot be empty.");
	}
	changeHistory.emplace_back(changedBy, "description", this->description, description, timestamp);
	this->description = description;
}

void Task::setPriority(TaskPriority priority, const User* changedBy, const Date& timestamp)
{
	changeHistory.emplace_back(changedBy, "priority", priorityToString(this->priority), priorityToString(priority), timestamp);
	this->priority = priority;
}

void Task::setStatus(TaskStatus status, const User* changedBy, const Date& timestamp)
{
	changeHistory.emplace_back(changedBy, "status", statusToString(this->status), statusToString(status), timestamp);
	this->status = status;
}

void Task::setAssignee(const User* user, const User* changedBy, const Date& timestamp)
{
	std::string oldVal = assignee ? assignee->getUsername() : "Unassigned";
	std::string newVal = user ? user->getUsername() : "Unassigned";
	changeHistory.emplace_back(changedBy, "assignee", oldVal, newVal, timestamp);
	this->assignee = user;
}

void Task::setDeadline(const Date& deadline, const User* changedBy, const Date& timestamp)
{
	changeHistory.emplace_back(changedBy, "deadline", this->deadline.toString(), deadline.toString(), timestamp);
	this->deadline = deadline;
}

void Task::setPoints(int points, const User* changedBy, const Date& timestamp)
{
	if (points < 0)
	{
		throw ValidationException("Points cannot be negative.");
	}
	changeHistory.emplace_back(changedBy, "points", std::to_string(this->points), std::to_string(points), timestamp);
	this->points = points;
}

void Task::setGrade(double grade, const User* changedBy, const Date& timestamp)
{
	if (grade < 2.0 || grade > 6.0)
	{
		throw ValidationException("Grade must be between 2 and 6.");
	}
	if (status != TaskStatus::Done)
	{
		throw StateException("Cannot grade a task that is not Done.");
	}
	changeHistory.emplace_back(changedBy, "grade", std::to_string(this->grade), std::to_string(grade), timestamp);
	this->grade = grade;
}

void Task::setApproved(bool approved, const User* changedBy, const Date& timestamp)
{
	std::string oldVal = this->approved ? "approved" : "not approved";
	std::string newVal = approved ? "approved" : "not approved";
	changeHistory.emplace_back(changedBy, "approval", oldVal, newVal, timestamp);
	this->approved = approved;
}

void Task::addComment(const Comment& comment)
{
	changeHistory.emplace_back(comment.getAuthor(), "comments", "", "added comment", comment.getCreationDate());
	comments.push_back(comment);
}

void Task::addTag(const std::string& tag, const User* changedBy, const Date& timestamp)
{
	if (tag.empty())
	{
		throw ValidationException("Tag cannot be empty.");
	}
	for (const auto& existing : tags)
	{
		if (existing == tag)
		{
			throw ValidationException("Tag '" + tag + "' already exists.");
		}
	}
	changeHistory.emplace_back(changedBy, "tags", "", tag, timestamp);
	tags.push_back(tag);
}

std::string Task::typeToString(TaskType type)
{
	switch (type)
	{
		case TaskType::Bug:
		    return "Bug";
		case TaskType::Feature:
		    return "Feature";
		case TaskType::Task:
		    return "Task";
		case TaskType::Improvement:
		    return "Improvement";
		default:
		    return "Unknown";
	}
}

std::string Task::priorityToString(TaskPriority priority)
{
	switch (priority)
	{
		case TaskPriority::Low:
		    return "Low";
		case TaskPriority::Medium:
		    return "Medium";
		case TaskPriority::High:
		    return "High";
		case TaskPriority::Critical:
		    return "Critical";
		default:
		    return "Unknown";
	}
}

std::string Task::statusToString(TaskStatus status)
{
	switch (status)
	{
		case TaskStatus::ToDo:
		    return "ToDo";
		case TaskStatus::InProgress:
		    return "InProgress";
		case TaskStatus::InReview:
		    return "InReview";
		case TaskStatus::Done:
		    return "Done";
		default:
		    return "Unknown";
	}
}

TaskType Task::parseType(const std::string& str)
{
	if (str == "Bug")
	    return TaskType::Bug;
	if (str == "Feature")
	    return TaskType::Feature;
	if (str == "Task")
	    return TaskType::Task;
	if (str == "Improvement")
	    return TaskType::Improvement;
	throw ValidationException("Unknown task type: " + str);
}

TaskPriority Task::parsePriority(const std::string& str)
{
	if (str == "Low")
	    return TaskPriority::Low;
	if (str == "Medium")
	    return TaskPriority::Medium;
	if (str == "High")
	    return TaskPriority::High;
	if (str == "Critical")
	    return TaskPriority::Critical;
	throw ValidationException("Unknown task priority: " + str);
}

TaskStatus Task::parseStatus(const std::string& str)
{
	if (str == "ToDo")
	    return TaskStatus::ToDo;
	if (str == "InProgress")
	    return TaskStatus::InProgress;
	if (str == "InReview")
	    return TaskStatus::InReview;
	if (str == "Done")
	    return TaskStatus::Done;
	throw ValidationException("Unknown task status: " + str);
}

std::ostream& operator<<(std::ostream& os, const Task& task)
{
	os << task.getFormattedId() << " | "
		<< Task::statusToString(task.status) << " | "
		<< Task::priorityToString(task.priority) << " | "
		<< Task::typeToString(task.type) << "\n"
		<< "  Title: " << task.title << "\n"
		<< "  Description: " << task.description << "\n"
		<< "  Deadline: " << task.deadline.toString() << "\n"
		<< "  Points: " << task.points << "\n";

	if (task.assignee)
	{
		os << "  Assignee: " << task.assignee->getUsername() << "\n";
	}
	else
	{
		os << "  Assignee: Unassigned\n";
	}

	if (task.grade > 0)
	{
		os << "  Grade: " << task.grade << "\n";
	}

	if (!task.tags.empty())
	{
		os << "  Tags: ";
		for (size_t i = 0; i < task.tags.size(); i++)
		{
			if (i > 0) os << ", ";
			os << task.tags[i];
		}
		os << "\n";
	}

	if (!task.comments.empty())
	{
		os << "  Comments (" << task.comments.size() << "):\n";
		for (const auto& comment : task.comments)
		{
			os << "    " << comment << "\n";
		}
	}

	return os;
}