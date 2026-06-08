#pragma once
#include "../base/Command.h"

class ApproveTaskCommand : public Command
{
public:
	ApproveTaskCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
