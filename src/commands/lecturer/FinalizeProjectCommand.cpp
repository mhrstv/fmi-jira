#include "FinalizeProjectCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/PermissionException.h"
#include "../../exceptions/NotFoundException.h"
#include "../../models/project/Project.h"

FinalizeProjectCommand::FinalizeProjectCommand() : Command("finalize-project", "Finalize a project") { }

void FinalizeProjectCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	if (args.empty())
	{
		throw ValidationException("Usage: finalize-project <project_name>");
	}

	std::string projectName = args[0];
	User* currentUser = data.getCurrentUser();
	if (currentUser->getRole() != Role::Lecturer && currentUser->getRole() != Role::Administrator)
	{
		throw PermissionException("Only Lecturers or Admins can finalize projects.");
	}

	Project* foundProject = nullptr;
	for (const auto& project : data.getProjects())
	{
		if (project->getName() == projectName)
		{
			foundProject = project.get();
			break;
		}
	}
	if (!foundProject)
	{
		throw NotFoundException("Project '" + projectName + "' not found.");
	}
	foundProject->finalize();
	data.os() << "[System] Project " << foundProject->getName() << " has been finalized.\n";
}
