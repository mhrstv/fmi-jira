#pragma once
#include "Command.h"

class CreateTaskCommand : public Command
{
public:
	CreateTaskCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
