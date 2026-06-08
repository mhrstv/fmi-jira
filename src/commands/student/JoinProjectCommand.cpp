#include "JoinProjectCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/NotFoundException.h"

JoinProjectCommand::JoinProjectCommand() : Command("join-project", "Join an existing project") { }

void JoinProjectCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	if (args.empty())
	{
		throw ValidationException("Usage: join-project <project_name>");
	}

	std::string name = args[0];
	Project* project = data.findProject(name);
	if (!project)
	{
		throw NotFoundException("Project '" + name + "' not found.");
	}
	User* currentUser = data.getCurrentUser();
	project->addMember(currentUser);

	data.os() << "[System] Successfully joined project '" << name << "'.\n";
}
