#pragma once
#include "../base/Command.h"

class FinishStageCommand : public Command
{
public:
	FinishStageCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
