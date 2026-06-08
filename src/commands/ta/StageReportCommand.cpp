#include "StageReportCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/PermissionException.h"
#include "../../exceptions/NotFoundException.h"
#include "../../models/project/Project.h"
#include "../../models/stage/Stage.h"
#include "../../models/task/Task.h"

StageReportCommand::StageReportCommand() : Command("stage-report", "Generate a report for a specific stage") { }

void StageReportCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	if (args.empty())
	{
		throw ValidationException("Usage: stage-report <stage_name>");
	}

	std::string stageName = args[0];
	User* currentUser = data.getCurrentUser();
	if (currentUser->getRole() != Role::TeachingAssistant && 
		currentUser->getRole() != Role::Lecturer && 
		currentUser->getRole() != Role::Administrator)
	{
		throw PermissionException("Only TAs, Lecturers or Admins can view stage reports.");
	}
	Stage* foundStage = nullptr;
	Project* foundProject = nullptr;
	for (const auto& project : data.getProjects())
	{
		if (project->hasMember(currentUser->getUsername()) || currentUser->getRole() == Role::Administrator)
		{
			Stage* stage = project->findStage(stageName);
			if (stage)
			{
				foundStage = stage;
				foundProject = project.get();
				break;
			}
		}
	}
	if (!foundStage)
	{
		throw NotFoundException("Stage '" + stageName + "' not found in any of your projects.");
	}

	int total = foundStage->getTotalTaskCount();
	int completed = foundStage->getCompletedTaskCount();

	data.os() << "Stage: " << foundStage->getName() << "\n";
	data.os() << "Tasks: " << total << "\n";
	data.os() << "Completed: " << completed << "\n";
}
