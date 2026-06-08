#pragma once
#include "../base/Command.h"

class StartStageCommand : public Command
{
public:
	StartStageCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
