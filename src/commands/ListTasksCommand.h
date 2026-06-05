#pragma once
#include "Command.h"

class ListTasksCommand : public Command
{
public:
	ListTasksCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
