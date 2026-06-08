#include "ArchiveProjectCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/PermissionException.h"
#include "../../exceptions/NotFoundException.h"

ArchiveProjectCommand::ArchiveProjectCommand() : Command("archive-project", "Archive a finalized project (Admin/Lecturer only)") { }

void ArchiveProjectCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	User* currentUser = data.getCurrentUser();
	if (currentUser->getRole() != Role::Administrator && currentUser->getRole() != Role::Lecturer)
	{
		throw PermissionException("Only administrators and lecturers can archive projects.");
	}

	if (args.empty())
	{
		throw ValidationException("Usage: archive-project <name>");
	}

	std::string name = args[0];

	Project* project = data.findProject(name);
	if (!project)
	{
		throw NotFoundException("Project '" + name + "' not found.");
	}

	project->archive();
	data.os() << "[System] Project '" << name << "' archived successfully.\n";
}
