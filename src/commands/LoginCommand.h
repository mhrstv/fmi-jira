#pragma once
#include "Command.h"

class LoginCommand : public Command
{
public:
	LoginCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
	bool requiresLogin() const override;
};
