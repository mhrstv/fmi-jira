#include "Stage.h"
#include "../task/Task.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/StateException.h"
#include "../../exceptions/NotFoundException.h"
#include "../../exceptions/DuplicateException.h"

Stage::Stage(const std::string& name) : name(name), startDate(), endDate(), status(StageStatus::Planned)
{
	if (name.empty())
	{
		throw ValidationException("Stage name cannot be empty.");
	}
}

const std::string& Stage::getName() const
{
	return name;
}

const Date& Stage::getStartDate() const
{
	return startDate;
}

const Date& Stage::getEndDate() const
{
	return endDate;
}

StageStatus Stage::getStatus() const
{
	return status;
}

const std::vector<Task*>& Stage::getTasks() const
{
	return tasks;
}

void Stage::start(const Date& startDate)
{
	if (status != StageStatus::Planned)
	{
		throw StateException("Stage '" + name + "' is not in Planned status.");
	}
	this->startDate = startDate;
	this->status = StageStatus::Active;
}

void Stage::finish(const Date& endDate)
{
	if (status != StageStatus::Active)
	{
		throw StateException("Stage '" + name + "' is not active.");
	}
	this->endDate = endDate;
	this->status = StageStatus::Finished;
}

void Stage::addTask(Task* task)
{
	if (!task)
	{
		throw ValidationException("Cannot add null task to stage.");
	}
	if (containsTask(task->getId()))
	{
		throw DuplicateException("Task " + task->getFormattedId() + " is already in stage '" + name + "'.");
	}
	tasks.push_back(task);
}

void Stage::removeTask(size_t taskId)
{
	for (auto it = tasks.begin(); it != tasks.end(); ++it)
	{
		if ((*it)->getId() == taskId)
		{
			tasks.erase(it);
			return;
		}
	}
	throw NotFoundException("Task with ID " + std::to_string(taskId) + " not found in stage '" + name + "'.");
}

bool Stage::containsTask(size_t taskId) const
{
	for (const auto* task : tasks)
	{
		if (task->getId() == taskId)
		{
			return true;
		}
	}
	return false;
}

int Stage::getTotalTaskCount() const
{
	return static_cast<int>(tasks.size());
}

int Stage::getCompletedTaskCount() const
{
	int count = 0;
	for (const auto* task : tasks)
	{
		if (task->getStatus() == TaskStatus::Done)
		{
			count++;
		}
	}
	return count;
}

std::string Stage::statusToString(StageStatus status)
{
	switch (status)
	{
		case StageStatus::Planned:
			return "Planned";
		case StageStatus::Active:
			return "Active";
		case StageStatus::Finished:
			return "Finished";
		default:
			return "Unknown";
	}
}

std::ostream& operator<<(std::ostream& os, const Stage& stage)
{
	os << "Stage: " << stage.name << "\n"
		<< "  Status: " << Stage::statusToString(stage.status) << "\n"
		<< "  Tasks: " << stage.getTotalTaskCount() << "\n"
		<< "  Completed: " << stage.getCompletedTaskCount() << "\n";

	if (stage.status != StageStatus::Planned)
	{
		os << "  Start: " << stage.startDate.toString() << "\n";
	}
	if (stage.status == StageStatus::Finished)
	{
		os << "  End: " << stage.endDate.toString() << "\n";
	}

	return os;
}