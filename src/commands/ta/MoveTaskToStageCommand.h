#pragma once
#include "../base/Command.h"

class MoveTaskToStageCommand : public Command
{
public:
	MoveTaskToStageCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
