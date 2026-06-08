#include "LogoutCommand.h"
#include "../../app/AppData.h"

LogoutCommand::LogoutCommand() : Command("logout", "Logout from the system") { }

void LogoutCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	data.setCurrentUser(nullptr);
	data.os() << "[System] Successfully logged out.\n";
}
