#include "ListAllTasksCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/PermissionException.h"
#include "../../models/project/Project.h"
#include "../../models/task/Task.h"

ListAllTasksCommand::ListAllTasksCommand() : Command("list-all-tasks", "List all tasks across all projects") { }

void ListAllTasksCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	User* currentUser = data.getCurrentUser();

	if (currentUser->getRole() != Role::Lecturer && currentUser->getRole() != Role::Administrator)
	{
		throw PermissionException("Only Lecturers and Admins can list all tasks.");
	}

	const auto& projects = data.getProjects();
	if (projects.empty())
	{
		data.os() << "[System] No tasks found.\n";
		return;
	}

	data.os() << "--- All Tasks ---\n";
	for (const auto& project : projects)
	{
		for (const auto& task : project->getTasks())
		{
			data.os() << *task << "\n";
		}
	}
}
