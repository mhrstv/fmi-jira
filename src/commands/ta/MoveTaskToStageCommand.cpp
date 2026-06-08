#include "MoveTaskToStageCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/PermissionException.h"
#include "../../exceptions/NotFoundException.h"
#include "../../models/project/Project.h"
#include "../../models/stage/Stage.h"
#include "../../models/task/Task.h"

MoveTaskToStageCommand::MoveTaskToStageCommand() : Command("move-task-to-stage", "Move a task to a specific stage") { }

void MoveTaskToStageCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	if (args.size() < 2)
	{
		throw ValidationException("Usage: move-task-to-stage <task_id> <stage_name>");
	}

	std::string taskIdStr = args[0];
	std::string stageName = args[1];
	User* currentUser = data.getCurrentUser();
	if (currentUser->getRole() != Role::TeachingAssistant && currentUser->getRole() != Role::Lecturer && currentUser->getRole() != Role::Administrator)
	{
		throw PermissionException("Only TAs, Lecturers or Admins can move tasks to stages.");
	}
	Task* foundTask = nullptr;
	Project* foundProject = nullptr;
	for (const auto& project : data.getProjects())
	{
		Task* task = project->findTaskByFormattedId(taskIdStr);
		if (task && (project->hasMember(currentUser->getUsername()) || currentUser->getRole() == Role::Administrator))
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
	Stage* targetStage = foundProject->findStage(stageName);
	if (!targetStage)
	{
		throw NotFoundException("Stage '" + stageName + "' not found in project " + foundProject->getName());
	}
	for (const auto& stage : foundProject->getStages())
	{
		if (stage->containsTask(foundTask->getId()))
		{
			stage->removeTask(foundTask->getId());
		}
	}

	targetStage->addTask(foundTask);
	data.os() << "[System] Task " << foundTask->getFormattedId() << " moved to stage " << stageName << ".\n";
}
