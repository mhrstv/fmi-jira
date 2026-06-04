#include "Command.h"

Command::Command(const std::string& name, const std::string& description) : name(name), description(description) { }

const std::string& Command::getName() const
{
	return name;
}

const std::string& Command::getDescription() const
{
	return description;
}

bool Command::requiresLogin() const
{
	return true;
}
