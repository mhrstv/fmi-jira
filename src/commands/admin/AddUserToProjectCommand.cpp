#include "AddUserToProjectCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/PermissionException.h"
#include "../../exceptions/NotFoundException.h"

AddUserToProjectCommand::AddUserToProjectCommand() : Command("add-user-to-project", "Add a user to a project (Admin/Lecturer only)") { }

void AddUserToProjectCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	User* currentUser = data.getCurrentUser();
	if (currentUser->getRole() != Role::Administrator && currentUser->getRole() != Role::Lecturer)
	{
		throw PermissionException("Only administrators and lecturers can add users to projects.");
	}

	if (args.size() < 2)
	{
		throw ValidationException("Usage: add-user-to-project <username> <project_name>");
	}

	std::string username = args[0];
	std::string projectName = args[1];

	User* userToAdd = data.findUser(username);
	if (!userToAdd)
	{
		throw NotFoundException("User '" + username + "' not found.");
	}

	Project* project = data.findProject(projectName);
	if (!project)
	{
		throw NotFoundException("Project '" + projectName + "' not found.");
	}

	project->addMember(userToAdd);

	data.os() << "[System] " << username << " added to project " << projectName << ".\n";
}

