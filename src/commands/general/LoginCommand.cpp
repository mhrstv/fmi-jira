#include "LoginCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/AuthException.h"
#include "../../exceptions/ValidationException.h"

LoginCommand::LoginCommand() : Command("login", "Login with username and password") { }

void LoginCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	if (data.getCurrentUser())
	{
		throw AuthException("Already logged in. Please logout first.");
	}
	if (args.size() < 2)
	{
		throw ValidationException("Usage: login <username> <password>");
	}

	const std::string& username = args[0];
	const std::string& password = args[1];

	User* user = data.findUser(username);
	if (!user)
	{
		throw AuthException("Invalid username or password.");
	}
	if (!user->checkPassword(password))
	{
		throw AuthException("Invalid username or password.");
	}

	data.setCurrentUser(user);
	data.os() << "[System] Successfully logged in. Role: " << user->getRoleString() << ".\n";
}

bool LoginCommand::requiresLogin() const
{
	return false;
}
