#include "Application.h"
#include <iostream>
#include <string>

#include "../commands/general/LoginCommand.h"
#include "../commands/general/LogoutCommand.h"
#include "../commands/general/HelpCommand.h"
#include "../commands/general/CloseCommand.h"
#include "../commands/general/ViewProfileCommand.h"
#include "../commands/general/SaveCommand.h"
#include "../commands/general/LoadCommand.h"
#include "../commands/admin/RegisterCommand.h"
#include "../commands/admin/CreateProjectCommand.h"
#include "../commands/admin/ArchiveProjectCommand.h"
#include "../commands/student/JoinProjectCommand.h"
#include "../commands/admin/AddUserToProjectCommand.h"

#include "../commands/student/CreateTaskCommand.h"
#include "../commands/student/AssignTaskCommand.h"
#include "../commands/student/ChangeStatusCommand.h"
#include "../commands/student/AddCommentCommand.h"
#include "../commands/student/AddTagCommand.h"
#include "../commands/student/ListProjectsCommand.h"
#include "../commands/student/ListTasksCommand.h"
#include "../commands/student/MyTasksCommand.h"
#include "../commands/student/UpcomingTasksCommand.h"
#include "../commands/student/SearchTasksCommand.h"
#include "../commands/student/FilterTasksCommand.h"

#include "../commands/ta/ApproveTaskCommand.h"
#include "../commands/ta/ReviewTaskCommand.h"
#include "../commands/ta/StartStageCommand.h"
#include "../commands/ta/FinishStageCommand.h"
#include "../commands/ta/StageReportCommand.h"
#include "../commands/ta/MoveTaskToStageCommand.h"

#include "../commands/lecturer/ListAllProjectsCommand.h"
#include "../commands/lecturer/ListAllTasksCommand.h"
#include "../commands/lecturer/GradeTaskCommand.h"
#include "../commands/lecturer/StudentReportCommand.h"
#include "../commands/lecturer/FinalizeProjectCommand.h"

Application::Application()
{
	data.load();
	registerCommands();
}

void Application::registerCommands()
{
	dispatcher.registerCommand(std::make_unique<LoginCommand>());
	dispatcher.registerCommand(std::make_unique<LogoutCommand>());
	dispatcher.registerCommand(std::make_unique<HelpCommand>());
	dispatcher.registerCommand(std::make_unique<CloseCommand>());
	dispatcher.registerCommand(std::make_unique<ViewProfileCommand>());
	dispatcher.registerCommand(std::make_unique<SaveCommand>());
	dispatcher.registerCommand(std::make_unique<LoadCommand>());
	dispatcher.registerCommand(std::make_unique<RegisterCommand>());
	dispatcher.registerCommand(std::make_unique<CreateProjectCommand>());
	dispatcher.registerCommand(std::make_unique<ArchiveProjectCommand>());
	dispatcher.registerCommand(std::make_unique<JoinProjectCommand>());
	dispatcher.registerCommand(std::make_unique<AddUserToProjectCommand>());
	
	dispatcher.registerCommand(std::make_unique<CreateTaskCommand>());
	dispatcher.registerCommand(std::make_unique<AssignTaskCommand>());
	dispatcher.registerCommand(std::make_unique<ChangeStatusCommand>());
	dispatcher.registerCommand(std::make_unique<AddCommentCommand>());
	dispatcher.registerCommand(std::make_unique<AddTagCommand>());
	dispatcher.registerCommand(std::make_unique<ListProjectsCommand>());
	dispatcher.registerCommand(std::make_unique<ListTasksCommand>());
	dispatcher.registerCommand(std::make_unique<MyTasksCommand>());
	dispatcher.registerCommand(std::make_unique<UpcomingTasksCommand>());

	dispatcher.registerCommand(std::make_unique<ApproveTaskCommand>());
	dispatcher.registerCommand(std::make_unique<ReviewTaskCommand>());
	dispatcher.registerCommand(std::make_unique<StartStageCommand>());
	dispatcher.registerCommand(std::make_unique<FinishStageCommand>());
	dispatcher.registerCommand(std::make_unique<StageReportCommand>());
	dispatcher.registerCommand(std::make_unique<MoveTaskToStageCommand>());

	dispatcher.registerCommand(std::make_unique<ListAllProjectsCommand>());
	dispatcher.registerCommand(std::make_unique<ListAllTasksCommand>());
	dispatcher.registerCommand(std::make_unique<GradeTaskCommand>());
	dispatcher.registerCommand(std::make_unique<StudentReportCommand>());
	dispatcher.registerCommand(std::make_unique<FinalizeProjectCommand>());

	dispatcher.registerCommand(std::make_unique<SearchTasksCommand>());
	dispatcher.registerCommand(std::make_unique<FilterTasksCommand>());
}

void Application::run()
{
	std::cout << "FMI JIRA - Project Management System\n";
	std::cout << "Type 'help' for a list of commands.\n\n";

	std::string input;
	while (data.isRunning())
	{
		std::cout << "> ";
		std::getline(std::cin, input);

		if (std::cin.eof())
		{
			break;
		}

		dispatcher.dispatch(input, data);
	}
}
