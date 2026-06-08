#include "ListAllProjectsCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/PermissionException.h"
#include "../../models/project/Project.h"

ListAllProjectsCommand::ListAllProjectsCommand() : Command("list-all-projects", "List all projects in the system") { }

void ListAllProjectsCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	User* currentUser = data.getCurrentUser();

	if (currentUser->getRole() != Role::Lecturer && currentUser->getRole() != Role::Administrator)
	{
		throw PermissionException("Only Lecturers and Admins can list all projects.");
	}

	const auto& projects = data.getProjects();
	if (projects.empty())
	{
		data.os() << "[System] No projects found in the system.\n";
		return;
	}

	for (const auto& project : projects)
	{
		data.os() << "- " << project->getName() << "\n";
	}
}
