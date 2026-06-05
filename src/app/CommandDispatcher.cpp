#include "CommandDispatcher.h"
#include "AppData.h"
#include "../exceptions/AppException.h"
#include "../exceptions/AuthException.h"
#include <iostream>

void CommandDispatcher::registerCommand(std::unique_ptr<Command> command)
{
	commands.push_back(std::move(command));
}

void CommandDispatcher::dispatch(const std::string& input, AppData& data)
{
	std::vector<std::string> commandParts;
	std::string currentPart = "";

	for (char c : input)
	{
		if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		{
			if (!currentPart.empty())
			{
				commandParts.push_back(currentPart);
				currentPart = "";
			}
		}
		else
		{
			currentPart += c;
		}
	}

	if (!currentPart.empty())
	{
		commandParts.push_back(currentPart);
	}

	if (commandParts.empty())
	{
		return;
	}

	std::string commandName = commandParts[0];

	Command* command = nullptr;
	for (const auto& cmd : commands)
	{
		if (cmd->getName() == commandName)
		{
			command = cmd.get();
			break;
		}
	}

	if (!command)
	{
		data.out() << "[System] Unknown command: " << commandName << ". Type 'help' for a list of commands.\n";
		return;
	}

	if (command->requiresLogin() && !data.getCurrentUser())
	{
		data.out() << "[System] You must be logged in to use this command.\n";
		return;
	}

	std::vector<std::string> args(commandParts.begin() + 1, commandParts.end());

	try
	{
		command->execute(args, data);
	}
	catch (const AppException& e)
	{
		data.out() << "[Error] " << e.what() << "\n";
	}
}

void CommandDispatcher::printHelp(std::ostream& os) const
{
	os << "Available commands:\n";
	for (const auto& command : commands)
	{
		os << "  " << command->getName() << " - " << command->getDescription() << "\n";
	}
}
