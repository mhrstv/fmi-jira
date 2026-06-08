#include "RegisterCommand.h"
#include "../../app/AppData.h"
#include "../../factories/UserFactory.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/PermissionException.h"
#include "../../exceptions/DuplicateException.h"
#include "../../enums/Role.h"

RegisterCommand::RegisterCommand() : Command("register", "Register a new user (Admin only)") { }

void RegisterCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	if (data.getCurrentUser()->getRole() != Role::Administrator)
	{
		throw PermissionException("Only administrators can register users.");
	}
	if (args.size() < 3)
	{
		throw ValidationException("Usage: register <username> <password> <role>");
	}

	const std::string& username = args[0];
	const std::string& password = args[1];
	const std::string& roleStr = args[2];

	if (data.findUser(username))
	{
		throw DuplicateException("User '" + username + "' already exists.");
	}

	Role role = UserFactory::parseRole(roleStr);
	auto user = UserFactory::createUser(username, password, role);
	data.addUser(std::move(user));

	data.os() << "[System] User '" << username << "' registered.\n";
}
