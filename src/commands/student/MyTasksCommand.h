#pragma once
#include "../base/Command.h"

class MyTasksCommand : public Command
{
public:
	MyTasksCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
