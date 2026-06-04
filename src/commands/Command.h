#pragma once
#include <string>
#include <vector>

class AppData;

class Command
{
	std::string name;
	std::string description;

public:
	Command(const std::string& name, const std::string& description);
	virtual ~Command() = default;

	const std::string& getName() const;
	const std::string& getDescription() const;

	virtual void execute(const std::vector<std::string>& args, AppData& context) = 0;
	virtual bool requiresLogin() const;
};
