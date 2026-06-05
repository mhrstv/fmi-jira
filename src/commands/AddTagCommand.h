#pragma once
#include "Command.h"

class AddTagCommand : public Command
{
public:
	AddTagCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
