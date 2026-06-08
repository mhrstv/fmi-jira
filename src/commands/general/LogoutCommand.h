#pragma once
#include "../base/Command.h"

class LogoutCommand : public Command
{
public:
	LogoutCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
