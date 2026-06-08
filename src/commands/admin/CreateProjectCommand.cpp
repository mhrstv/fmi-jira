#include "CreateProjectCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/PermissionException.h"
#include "../../exceptions/DuplicateException.h"
#include "../../enums/Role.h"

CreateProjectCommand::CreateProjectCommand() : Command("create-project", "Create a new project (Admin/Lecturer only)") { }

void CreateProjectCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	User* currentUser = data.getCurrentUser();
	if (currentUser->getRole() != Role::Administrator && currentUser->getRole() != Role::Lecturer)
	{
		throw PermissionException("Only administrators and lecturers can create projects.");
	}

	if (args.empty())
	{
		throw ValidationException("Usage: create-project <name> [description...]");
	}

	std::string name = args[0];
	std::string description = "";
	
	for (size_t i = 1; i < args.size(); ++i)
	{
		description += args[i];
		if (i < args.size() - 1)
		{
			description += " ";
		}
	}

	if (data.findProject(name))
	{
		throw DuplicateException("Project '" + name + "' already exists.");
	}

	auto project = std::make_unique<Project>(name, description);
	data.addProject(std::move(project));

	data.os() << "[System] Project '" << name << "' created successfully.\n";
}
