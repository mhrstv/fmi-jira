#include "AddTagCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/PermissionException.h"
#include "../../exceptions/NotFoundException.h"
#include "../../models/task/Task.h"
#include "../../utils/Date.h"

AddTagCommand::AddTagCommand() : Command("add-tag", "Add a tag to a task") { }

void AddTagCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	if (args.size() < 2)
	{
		throw ValidationException("Usage: add-tag <task_id> <tag>");
	}

	std::string taskIdStr = args[0];
	std::string tagStr = args[1];
	User* currentUser = data.getCurrentUser();
	Task* foundTask = nullptr;
	Project* foundProject = nullptr;
	for (const auto& project : data.getProjects())
	{
		Task* task = project->findTaskByFormattedId(taskIdStr);
		if (task)
		{
			foundTask = task;
			foundProject = project.get();
			break;
		}
	}
	if (!foundTask)
	{
		throw NotFoundException("Task '" + taskIdStr + "' not found.");
	}
	if (!foundProject->hasMember(currentUser->getUsername()) && currentUser->getRole() != Role::Administrator)
	{
		throw PermissionException("You must be a member of the project to add tags to its tasks.");
	}
	
	foundTask->addTag(tagStr, currentUser, Date());
}
