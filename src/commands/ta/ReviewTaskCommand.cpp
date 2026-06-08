#include "ReviewTaskCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/PermissionException.h"
#include "../../exceptions/NotFoundException.h"
#include "../../models/project/Project.h"
#include "../../models/task/Task.h"
#include "../../utils/Date.h"

ReviewTaskCommand::ReviewTaskCommand() : Command("review-task", "Mark a task for review") { }

void ReviewTaskCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	if (args.empty())
	{
		throw ValidationException("Usage: review-task <task_id>");
	}

	std::string taskIdStr = args[0];
	User* currentUser = data.getCurrentUser();
	if (currentUser->getRole() != Role::TeachingAssistant && 
		currentUser->getRole() != Role::Lecturer && 
		currentUser->getRole() != Role::Administrator)
	{
		throw PermissionException("Only TAs, Lecturers or Admins can review tasks.");
	}

	Task* foundTask = nullptr;
	for (const auto& project : data.getProjects())
	{
		Task* task = project->findTaskByFormattedId(taskIdStr);
		if (task && (project->hasMember(currentUser->getUsername()) || currentUser->getRole() == Role::Administrator))
		{
			foundTask = task;
			break;
		}
	}
	if (!foundTask)
	{
		throw NotFoundException("Task '" + taskIdStr + "' not found.");
	}

	foundTask->setStatus(TaskStatus::InReview, currentUser, Date());
	data.os() << "[System] Task reviewed.\n";
}
