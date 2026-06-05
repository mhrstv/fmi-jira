#pragma once
#include "Command.h"

class JoinProjectCommand : public Command
{
public:
	JoinProjectCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
