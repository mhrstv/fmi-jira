#pragma once
#include "../base/Command.h"

class SaveCommand : public Command
{
public:
	SaveCommand();

	void execute(const std::vector<std::string>& args, AppData& data) override;
};

