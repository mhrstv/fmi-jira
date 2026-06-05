#include "UpcomingTasksCommand.h"
#include "../app/AppData.h"
#include "../models/project/Project.h"
#include "../models/task/Task.h"

UpcomingTasksCommand::UpcomingTasksCommand() : Command("upcoming-tasks", "List your incomplete tasks") { }

void UpcomingTasksCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	User* currentUser = data.getCurrentUser();
	bool found = false;

	for (const auto& project : data.getProjects())
	{
		for (const auto& task : project->getTasks())
		{
			if (task->getAssignee() == currentUser && task->getStatus() != TaskStatus::Done)
			{
				data.out() << "- " << task->getFormattedId() << " | " << task->getTitle() << "\n";
				found = true;
			}
		}
	}

	if (!found)
	{
		data.out() << "No upcoming tasks.\n";
	}
}
