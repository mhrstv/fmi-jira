#pragma once
#include "Command.h"

class AddCommentCommand : public Command
{
public:
	AddCommentCommand();
	void execute(const std::vector<std::string>& args, AppData& data) override;
};
