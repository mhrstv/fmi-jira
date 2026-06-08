#pragma once
#include "../base/Command.h"

class StudentReportCommand : public Command
{
public:
	StudentReportCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
