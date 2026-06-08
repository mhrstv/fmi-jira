#pragma once
#include "../base/Command.h"

class ListProjectsCommand : public Command
{
public:
	ListProjectsCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
