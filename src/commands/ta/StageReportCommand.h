#pragma once
#include "../base/Command.h"

class StageReportCommand : public Command
{
public:
	StageReportCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
