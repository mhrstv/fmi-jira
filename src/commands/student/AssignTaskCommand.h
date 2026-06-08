#pragma once
#include "../base/Command.h"

class AssignTaskCommand : public Command
{
public:
	AssignTaskCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
