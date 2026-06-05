#include "Project.h"
#include "../../users/User.h"
#include "../task/Task.h"
#include "../stage/Stage.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/StateException.h"
#include "../../exceptions/NotFoundException.h"
#include "../../exceptions/DuplicateException.h"

Project::Project(const std::string& name, const std::string& description) : name(name), description(description), status(ProjectStatus::Active)
{
	if (name.empty())
	{
		throw ValidationException("Project name cannot be empty.");
	}
}

Project::~Project() = default;

const std::string& Project::getName() const
{
	return name;
}

const std::string& Project::getDescription() const
{
	return description;
}

ProjectStatus Project::getStatus() const
{
	return status;
}

const std::vector<User*>& Project::getMembers() const
{
	return members;
}

const std::vector<std::unique_ptr<Task>>& Project::getTasks() const
{
	return tasks;
}

const std::vector<std::unique_ptr<Stage>>& Project::getStages() const
{
	return stages;
}

void Project::setDescription(const std::string& description)
{
	this->description = description;
}

void Project::addMember(User* user)
{
	if (!user)
	{
		throw ValidationException("Cannot add null user to project.");
	}
	if (hasMember(user->getUsername()))
	{
		throw DuplicateException("User '" + user->getUsername() + "' is already a member of project '" + name + "'.");
	}
	members.push_back(user);
}

void Project::removeMember(const std::string& username)
{
	for (auto it = members.begin(); it != members.end(); ++it)
	{
		if ((*it)->getUsername() == username)
		{
			members.erase(it);
			return;
		}
	}
	throw NotFoundException("User '" + username + "' is not a member of project '" + name + "'.");
}

bool Project::hasMember(const std::string& username) const
{
	for (const auto* member : members)
	{
		if (member->getUsername() == username)
		{
			return true;
		}
	}
	return false;
}

User* Project::findMember(const std::string& username) const
{
	for (auto* member : members)
	{
		if (member->getUsername() == username)
		{
			return member;
		}
	}
	return nullptr;
}

Task* Project::addTask(std::unique_ptr<Task> task)
{
	if (!task)
	{
		throw ValidationException("Cannot add null task to project.");
	}
	Task* ptr = task.get();
	tasks.push_back(std::move(task));
	return ptr;
}

Task* Project::findTask(size_t taskId) const
{
	for (const auto& task : tasks)
	{
		if (task->getId() == taskId)
		{
			return task.get();
		}
	}
	return nullptr;
}

Task* Project::findTaskByFormattedId(const std::string& formattedId) const
{
	for (const auto& task : tasks)
	{
		if (task->getFormattedId() == formattedId)
		{
			return task.get();
		}
	}
	return nullptr;
}

Stage* Project::addStage(std::unique_ptr<Stage> stage)
{
	if (!stage)
	{
		throw ValidationException("Cannot add null stage to project.");
	}
	if (findStage(stage->getName()))
	{
		throw DuplicateException("Stage '" + stage->getName() + "' already exists in project '" + name + "'.");
	}
	Stage* ptr = stage.get();
	stages.push_back(std::move(stage));
	return ptr;
}

Stage* Project::findStage(const std::string& stageName) const
{
	for (const auto& stage : stages)
	{
		if (stage->getName() == stageName)
		{
			return stage.get();
		}
	}
	return nullptr;
}

void Project::finalize()
{
	if (status != ProjectStatus::Active)
	{
		throw StateException("Project '" + name + "' is not active.");
	}
	status = ProjectStatus::Finished;
}

void Project::archive()
{
	if (status != ProjectStatus::Finished)
	{
		throw StateException("Project '" + name + "' must be finalized before archiving.");
	}
	status = ProjectStatus::Finished;
}

std::string Project::statusToString(ProjectStatus status)
{
	switch (status)
	{
		case ProjectStatus::Active:
			return "Active";
		case ProjectStatus::Finished:
			return "Finished";
		default:
			return "Unknown";
	}
}

std::ostream& operator<<(std::ostream& os, const Project& project)
{
	os << "Project: " << project.name << "\n"
	   << "  Status: " << Project::statusToString(project.status) << "\n";

	if (!project.description.empty())
	{
		os << "  Description: " << project.description << "\n";
	}

	os << "  Members: " << project.members.size() << "\n"
		<< "  Tasks: " << project.tasks.size() << "\n"
		<< "  Stages: " << project.stages.size() << "\n";

	return os;
}