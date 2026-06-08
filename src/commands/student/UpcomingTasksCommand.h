#pragma once
#include "../base/Command.h"

class UpcomingTasksCommand : public Command
{
public:
	UpcomingTasksCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
