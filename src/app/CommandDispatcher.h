#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../commands/Command.h"

class AppData;

class CommandDispatcher
{
	std::vector<std::unique_ptr<Command>> commands;

public:
	void registerCommand(std::unique_ptr<Command> command);
	void dispatch(const std::string& input, AppData& data);
	void printHelp(std::ostream& os) const;
};
