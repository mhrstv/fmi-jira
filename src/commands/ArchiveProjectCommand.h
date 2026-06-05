#pragma once
#include "Command.h"

class ArchiveProjectCommand : public Command
{
public:
	ArchiveProjectCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};	
