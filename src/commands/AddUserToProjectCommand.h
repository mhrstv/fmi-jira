#pragma once
#include "Command.h"

class AddUserToProjectCommand : public Command
{
public:
	AddUserToProjectCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
