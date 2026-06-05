#pragma once
#include "Command.h"

class RegisterCommand : public Command
{
public:
	RegisterCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
