#include "AddCommentCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/PermissionException.h"
#include "../../exceptions/NotFoundException.h"
#include "../../models/task/Task.h"
#include "../../utils/Date.h"

AddCommentCommand::AddCommentCommand() : Command("add-comment", "Add a comment to a task") { }

void AddCommentCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	if (args.empty())
	{
		throw ValidationException("Usage: add-comment <task_id>");
	}

	std::string taskIdStr = args[0];
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
		throw PermissionException("You must be a member of the project to comment on its tasks.");
	}

	std::string commentStr;
	data.os() << "Comment: ";
	std::getline(data.is(), commentStr);
	Comment comment(currentUser, commentStr, Date());
	foundTask->addComment(comment);

	data.os() << "[System] Comment added.\n";
}
