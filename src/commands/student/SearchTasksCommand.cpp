#include "SearchTasksCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/ValidationException.h"
#include "../../models/project/Project.h"
#include "../../models/task/Task.h"

SearchTasksCommand::SearchTasksCommand() : Command("search-tasks", "Search tasks by keyword") { }

void SearchTasksCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	if (args.empty())
	{
		throw ValidationException("Usage: search-tasks <keyword>");
	}

	std::string keyword = args[0];
	User* currentUser = data.getCurrentUser();
	bool found = false;
	for (const auto& project : data.getProjects())
	{
		if (project->hasMember(currentUser->getUsername()) || currentUser->getRole() == Role::Administrator)
		{
			for (const auto& task : project->getTasks())
			{
				if (task->getTitle().find(keyword) != std::string::npos || task->getDescription().find(keyword) != std::string::npos)
				{
					data.os() << "- " << task->getFormattedId() << " | " << task->getTitle() << "\n";
					found = true;
				}
			}
		}
	}
	if (!found)
	{
		data.os() << "No tasks match the keyword.\n";
	}
}
