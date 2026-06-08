#pragma once
#include "../base/Command.h"

class ReviewTaskCommand : public Command
{
public:
	ReviewTaskCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
