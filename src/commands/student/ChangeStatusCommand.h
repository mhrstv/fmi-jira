#pragma once
#include "../base/Command.h"

class ChangeStatusCommand : public Command
{
public:
	ChangeStatusCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
