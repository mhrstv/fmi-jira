#include "MyTasksCommand.h"
#include "../../app/AppData.h"
#include "../../models/project/Project.h"
#include "../../models/task/Task.h"

MyTasksCommand::MyTasksCommand() : Command("my-tasks", "View your tasks and performance") { }

void MyTasksCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	User* currentUser = data.getCurrentUser();
	int completed = 0;
	int inProgress = 0;
	int score = 0;
	for (const auto& project : data.getProjects())
	{
		for (const auto& task : project->getTasks())
		{
			if (task->getAssignee() == currentUser)
			{
				if (task->getStatus() == TaskStatus::Done)
				{
					completed++;
					score += 10;
				}
				else if (task->getStatus() == TaskStatus::InProgress)
				{
					inProgress++;
				}
			}
		}
	}
	data.os() << "Completed tasks: " << completed << "\n"
			   << "In progress: " << inProgress << "\n"
			   << "Performance score: " << score << "\n";
}
