#include "StartStageCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/PermissionException.h"
#include "../../exceptions/NotFoundException.h"
#include "../../models/project/Project.h"
#include "../../models/stage/Stage.h"
#include "../../utils/Date.h"

StartStageCommand::StartStageCommand() : Command("start-stage", "Start a project stage") { }

void StartStageCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	if (args.empty())
	{
		throw ValidationException("Usage: start-stage <stage_name>");
	}

	std::string stageName = args[0];
	User* currentUser = data.getCurrentUser();

	if (currentUser->getRole() != Role::TeachingAssistant && currentUser->getRole() != Role::Lecturer && currentUser->getRole() != Role::Administrator)
	{
		throw PermissionException("Only TAs, Lecturers or Admins can start stages.");
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
		for (const auto& project : data.getProjects())
		{
			if (project->hasMember(currentUser->getUsername()) || currentUser->getRole() == Role::Administrator)
			{
				foundProject = project.get();
				break;
			}
		}
		if (!foundProject)
		{
			throw PermissionException("You are not a member of any project to create a stage in.");
		}
		auto newStage = std::make_unique<Stage>(stageName);
		foundStage = foundProject->addStage(std::move(newStage));
	}

	foundStage->start(Date());
	data.os() << "[System] Stage '" << foundStage->getName() << "' started.\n";
}
