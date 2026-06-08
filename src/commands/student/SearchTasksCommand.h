#pragma once
#include "../base/Command.h"

class SearchTasksCommand : public Command
{
public:
	SearchTasksCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
