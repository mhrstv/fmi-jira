#pragma once
#include "../base/Command.h"

class ListAllTasksCommand : public Command
{
public:
	ListAllTasksCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
