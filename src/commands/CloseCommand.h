#pragma once
#include "Command.h"

class CloseCommand : public Command
{
public:
	CloseCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
	bool requiresLogin() const override;
};
