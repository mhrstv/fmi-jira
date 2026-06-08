#include "LoadCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/PermissionException.h"
#include "../../users/Administrator.h"
#include <stdexcept>

LoadCommand::LoadCommand() : Command("load", "Load the system state from a file") { }

void LoadCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	User* currentUser = data.getCurrentUser();
	if (currentUser->getRole() != Role::Administrator)
	{
		throw PermissionException("Only Administrators can load the system state.");
	}
	try
	{
		data.load();
		data.os() << "[System] Data loaded successfully.\n";
	}
	catch (const std::exception& e)
	{
		data.os() << "[Error] Failed to load state: " << e.what() << "\n";
	}
}