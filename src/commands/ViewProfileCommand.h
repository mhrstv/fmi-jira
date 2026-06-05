#pragma once
#include "Command.h"

class ViewProfileCommand : public Command
{
public:
	ViewProfileCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
