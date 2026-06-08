#pragma once
#include "../base/Command.h"

class ListAllProjectsCommand : public Command
{
public:
	ListAllProjectsCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
