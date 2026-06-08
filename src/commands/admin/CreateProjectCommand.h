#pragma once
#include "../base/Command.h"

class CreateProjectCommand : public Command
{
public:
	CreateProjectCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
