#include "Task.h"
#include "../../users/User.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/StateException.h"

size_t Task::idGen = 100;

Task::Task(const std::string& title, const std::string& description, TaskType type, TaskPriority priority, const Date& deadline)
	: id(++idGen), title(title), description(description), type(type), priority(priority),
	  status(TaskStatus::ToDo), assignee(nullptr), deadline(deadline), points(0), grade(0.0), approved(false)
{
	if (title.empty())
	{
		throw ValidationException("Task title cannot be empty.");
	}
	if (description.empty())
	{
		throw ValidationException("Task description cannot be empty.");
	}
	changeHistory.push_back("Task " + getFormattedId() + " created.");
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

const std::vector<std::string>& Task::getChangeHistory() const
{
	return changeHistory;
}

void Task::setTitle(const std::string& title)
{
	if (title.empty())
	{
		throw ValidationException("Task title cannot be empty.");
	}
	changeHistory.push_back("Title changed from '" + this->title + "' to '" + title + "'.");
	this->title = title;
}

void Task::setDescription(const std::string& description)
{
	if (description.empty())
	{
		throw ValidationException("Task description cannot be empty.");
	}
	changeHistory.push_back("Description updated.");
	this->description = description;
}

void Task::setPriority(TaskPriority priority)
{
	changeHistory.push_back("Priority changed from " + priorityToString(this->priority) + " to " + priorityToString(priority) + ".");
	this->priority = priority;
}

void Task::setStatus(TaskStatus status)
{
	changeHistory.push_back("Status changed from " + statusToString(this->status) + " to " + statusToString(status) + ".");
	this->status = status;
}

void Task::setAssignee(const User* user)
{
	if (user)
	{
		changeHistory.push_back("Assigned to " + user->getUsername() + ".");
	}
	else
	{
		changeHistory.push_back("Assignee removed.");
	}
	this->assignee = user;
}

void Task::setDeadline(const Date& deadline)
{
	changeHistory.push_back("Deadline changed to " + deadline.toString() + ".");
	this->deadline = deadline;
}

void Task::setPoints(int points)
{
	if (points < 0)
	{
		throw ValidationException("Points cannot be negative.");
	}
	changeHistory.push_back("Points set to " + std::to_string(points) + ".");
	this->points = points;
}

void Task::setGrade(double grade)
{
	if (grade < 2.0 || grade > 6.0)
	{
		throw ValidationException("Grade must be between 2 and 6.");
	}
	if (status != TaskStatus::Done)
	{
		throw StateException("Cannot grade a task that is not Done.");
	}
	changeHistory.push_back("Graded: " + std::to_string(grade) + ".");
	this->grade = grade;
}

void Task::setApproved(bool approved)
{
	if (approved)
	{
		changeHistory.push_back("Task approved.");
	}
	this->approved = approved;
}

void Task::addComment(const Comment& comment)
{
	changeHistory.push_back("Comment added by " + std::string(comment.getAuthor()->getUsername()) + ".");
	comments.push_back(comment);
}

void Task::addTag(const std::string& tag)
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
	changeHistory.push_back("Tag '" + tag + "' added.");
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