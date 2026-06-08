#include "ListTasksCommand.h"
#include "../../app/AppData.h"
#include "../../models/project/Project.h"
#include "../../models/task/Task.h"

ListTasksCommand::ListTasksCommand() : Command("list-tasks", "List all tasks in your projects") { }

void ListTasksCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	User* currentUser = data.getCurrentUser();
	bool found = false;
	for (const auto& project : data.getProjects())
	{
		if (project->hasMember(currentUser->getUsername()) || currentUser->getRole() == Role::Administrator)
		{
			for (const auto& task : project->getTasks())
			{
				data.os() << "- " << task->getFormattedId() << " | " 
						   << Task::statusToString(task->getStatus()) << " | " 
						   << Task::priorityToString(task->getPriority()) << "\n";
				found = true;
			}
		}
	}
	if (!found)
	{
		data.os() << "No tasks found.\n";
	}
}
