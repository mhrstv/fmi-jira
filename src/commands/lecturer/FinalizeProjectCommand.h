#pragma once
#include "../base/Command.h"

class FinalizeProjectCommand : public Command
{
public:
	FinalizeProjectCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
