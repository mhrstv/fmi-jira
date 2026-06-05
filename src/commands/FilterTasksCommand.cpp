#include "FilterTasksCommand.h"
#include "../app/AppData.h"
#include "../exceptions/ValidationException.h"
#include "../models/project/Project.h"
#include "../models/task/Task.h"

FilterTasksCommand::FilterTasksCommand() : Command("filter-tasks", "Filter tasks by status, priority, or type") { }

void FilterTasksCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	if (args.empty())
	{
		throw ValidationException("Usage: filter-tasks <criteria>");
	}

	std::string criteria = args[0];
	User* currentUser = data.getCurrentUser();
	bool found = false;

	for (const auto& project : data.getProjects())
	{
		if (project->hasMember(currentUser->getUsername()) || currentUser->getRole() == Role::Administrator)
		{
			for (const auto& task : project->getTasks())
			{
				if (Task::statusToString(task->getStatus()) == criteria ||
					Task::priorityToString(task->getPriority()) == criteria ||
					Task::typeToString(task->getType()) == criteria)
				{
					data.out() << "- " << task->getFormattedId() << " | " << task->getTitle() << "\n";
					found = true;
				}
			}
		}
	}

	if (!found)
	{
		data.out() << "No tasks match the filter.\n";
	}
}
