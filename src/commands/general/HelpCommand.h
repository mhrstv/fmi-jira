#pragma once
#include "../base/Command.h"

class HelpCommand : public Command
{
public:
	HelpCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
	bool requiresLogin() const override;
};
