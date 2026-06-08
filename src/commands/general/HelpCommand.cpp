#include "HelpCommand.h"
#include "../../app/AppData.h"
#include "../../app/CommandDispatcher.h"

HelpCommand::HelpCommand() : Command("help", "Show available commands") { }

void HelpCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	data.os() << "FMI JIRA - Available commands:\n"
				<< "  login <username> <password>  - Login to the system\n"
				<< "  logout                       - Logout from the system\n"
				<< "  register <user> <pass> <role> - Register a new user (Admin only)\n"
				<< "  view-profile                 - View your profile\n"
				<< "  help                         - Show this help message\n"
				<< "  close                        - Exit the application\n";
}

bool HelpCommand::requiresLogin() const
{
	return false;
}
