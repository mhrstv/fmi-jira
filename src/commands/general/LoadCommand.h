#pragma once
#include "../base/Command.h"

class LoadCommand : public Command
{
public:
	LoadCommand();

	void execute(const std::vector<std::string>& args, AppData& data) override;
};
