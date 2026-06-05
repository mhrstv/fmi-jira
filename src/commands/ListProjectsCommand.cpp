#include "ListProjectsCommand.h"
#include "../app/AppData.h"
#include "../models/project/Project.h"

ListProjectsCommand::ListProjectsCommand() : Command("list-projects", "List all projects you are a member of") { }

void ListProjectsCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	User* currentUser = data.getCurrentUser();
	bool found = false;

	for (const auto& project : data.getProjects())
	{
		if (project->hasMember(currentUser->getUsername()) || currentUser->getRole() == Role::Administrator)
		{
			data.out() << "- " << project->getName() << "\n";
			found = true;
		}
	}

	if (!found)
	{
		data.out() << "You are not a member of any projects.\n";
	}
}
