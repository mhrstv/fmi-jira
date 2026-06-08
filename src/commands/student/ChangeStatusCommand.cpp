#include "ChangeStatusCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/PermissionException.h"
#include "../../exceptions/NotFoundException.h"
#include "../../models/task/Task.h"
#include "../../utils/Date.h"

ChangeStatusCommand::ChangeStatusCommand() : Command("change-status", "Change status of a task") { }

void ChangeStatusCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	if (args.size() < 2)
	{
		throw ValidationException("Usage: change-status <task_id> <status>");
	}

	std::string taskIdStr = args[0];
	std::string statusStr = args[1];
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
		throw PermissionException("You must be a member of the project to change its task's status.");
	}
	if (foundTask->getAssignee() != currentUser && currentUser->getRole() == Role::Student)
	{
		throw PermissionException("You must be assigned to the task to change its status.");
	}
	TaskStatus newStatus = Task::parseStatus(statusStr);
	foundTask->setStatus(newStatus, currentUser, Date());

	if (newStatus == TaskStatus::Done) {
		data.os() << "[System] Task marked as Done.\n";
	} else {
		data.os() << "[System] Status updated successfully.\n";
	}
}

