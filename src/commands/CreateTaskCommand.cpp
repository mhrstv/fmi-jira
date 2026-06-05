#include "CreateTaskCommand.h"
#include "../app/AppData.h"
#include "../exceptions/ValidationException.h"
#include "../exceptions/PermissionException.h"
#include "../exceptions/NotFoundException.h"
#include "../models/task/Task.h"
#include <iostream>

CreateTaskCommand::CreateTaskCommand() : Command("create-task", "Create a new task in a project") { }

void CreateTaskCommand::execute(const std::vector<std::string>& args, AppData& data)
{
	if (args.size() < 3)
	{
		throw ValidationException("Usage: create-task <project_name> <type> <priority>");
	}

	std::string projectName = args[0];
	std::string typeStr = args[1];
	std::string priorityStr = args[2];

	Project* project = data.findProject(projectName);
	if (!project)
	{
		throw NotFoundException("Project '" + projectName + "' not found.");
	}

	User* currentUser = data.getCurrentUser();
	if (!project->hasMember(currentUser->getUsername()) && currentUser->getRole() != Role::Administrator)
	{
		throw PermissionException("You must be a member of the project to create tasks in it.");
	}

	TaskType type = Task::parseType(typeStr);
	TaskPriority priority = Task::parsePriority(priorityStr);

	std::string title;
	std::string description;

	data.out() << "Title: ";
	std::getline(data.in(), title);
	
	data.out() << "Description: ";
	std::getline(data.in(), description);

	auto task = std::make_unique<Task>(title, description, type, priority);
	Task* created = project->addTask(std::move(task));

	data.out() << "[System] Task " << created->getFormattedId() << " created successfully.\n";
}
