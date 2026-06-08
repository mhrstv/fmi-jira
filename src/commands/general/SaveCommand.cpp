#include "SaveCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/PermissionException.h"
#include "../../users/Administrator.h"
#include <stdexcept>

SaveCommand::SaveCommand() : Command("save", "Save the current system state to a file") { }

void SaveCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	User* currentUser = data.getCurrentUser();
	if (currentUser->getRole() != Role::Administrator)
	{
		throw PermissionException("Only Administrators can save the system state.");
	}
	try
	{
		data.save();
		data.os() << "[System] Data saved successfully.\n";
	}
	catch (const std::exception& e)
	{
		data.os() << "[Error] Failed to save state: " << e.what() << "\n";
	}
}

