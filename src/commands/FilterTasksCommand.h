#pragma once
#include "Command.h"

class FilterTasksCommand : public Command
{
public:
	FilterTasksCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
