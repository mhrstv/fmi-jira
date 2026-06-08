#pragma once
#include "../base/Command.h"

class GradeTaskCommand : public Command
{
public:
	GradeTaskCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
