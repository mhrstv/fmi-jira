#include "Stage.h"
#include "../task/Task.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/StateException.h"
#include "../../exceptions/NotFoundException.h"
#include "../../utils/DataStream.h"
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

void Stage::save(std::ostream& os) const
{
	DataStream::writeString(os, name);
	DataStream::writeString(os, startDate.toString());
	DataStream::writeString(os, endDate.toString());
	DataStream::writeInt(os, static_cast<int>(status));

	DataStream::writeSizeT(os, tasks.size());
	for (Task* task : tasks)
	{
		DataStream::writeSizeT(os, task->getId());
	}
}

std::unique_ptr<Stage> Stage::load(std::istream& is, const std::vector<std::unique_ptr<Task>>& projectTasks)
{
	auto stage = std::make_unique<Stage>();
	stage->name = DataStream::readString(is);
	stage->startDate = Date::parse(DataStream::readString(is));
	stage->endDate = Date::parse(DataStream::readString(is));
	stage->status = static_cast<StageStatus>(DataStream::readInt(is));

	size_t tasksCount = DataStream::readSizeT(is);
	for (size_t i = 0; i < tasksCount; i++)
	{
		size_t taskId = DataStream::readSizeT(is);
		for (const auto& t : projectTasks)
		{
			if (t->getId() == taskId)
			{
				stage->tasks.push_back(t.get());
				break;
			}
		}
	}
	return stage;
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