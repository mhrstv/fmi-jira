#include "CloseCommand.h"
#include "../app/AppData.h"

CloseCommand::CloseCommand() : Command("close", "Exit the application") { }

void CloseCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	data.out() << "[System] System shutting down...\n";
	data.stop();
}

bool CloseCommand::requiresLogin() const
{
	return false;
}
