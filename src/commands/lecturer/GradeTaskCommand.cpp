#include "GradeTaskCommand.h"
#include "../../app/AppData.h"
#include "../../exceptions/ValidationException.h"
#include "../../exceptions/PermissionException.h"
#include "../../exceptions/NotFoundException.h"
#include "../../models/project/Project.h"
#include "../../models/task/Task.h"
#include "../../utils/Date.h"
#include <string>

GradeTaskCommand::GradeTaskCommand() : Command("grade-task", "Grade a task") { }

void GradeTaskCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	if (args.size() < 2)
	{
		throw ValidationException("Usage: grade-task <task_id> <grade>");
	}

	std::string taskIdStr = args[0];
	double grade = 0.0;
	try
	{
		grade = std::stod(args[1]);
	}
	catch (...)
	{
		throw ValidationException("Grade must be a valid number.");
	}

	User* currentUser = data.getCurrentUser();
	if (currentUser->getRole() != Role::Lecturer && currentUser->getRole() != Role::Administrator)
	{
		throw PermissionException("Only Lecturers or Admins can grade tasks.");
	}

	Task* foundTask = nullptr;
	for (const auto& project : data.getProjects())
	{
		Task* task = project->findTaskByFormattedId(taskIdStr);
		if (task)
		{
			foundTask = task;
			break;
		}
	}
	if (!foundTask)
	{
		throw NotFoundException("Task '" + taskIdStr + "' not found.");
	}

	foundTask->setGrade(grade, currentUser, Date());
	data.os() << "[System] Task graded successfully.\n";
}

