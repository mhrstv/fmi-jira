#include "Application.h"
#include "../commands/LoginCommand.h"
#include "../commands/LogoutCommand.h"
#include "../commands/HelpCommand.h"
#include "../commands/CloseCommand.h"
#include "../commands/ViewProfileCommand.h"
#include "../commands/RegisterCommand.h"
#include "../commands/CreateProjectCommand.h"
#include "../commands/ArchiveProjectCommand.h"
#include "../commands/JoinProjectCommand.h"
#include "../commands/AddUserToProjectCommand.h"
#include <iostream>
#include <string>

Application::Application()
{
	registerCommands();
}

void Application::registerCommands()
{
	dispatcher.registerCommand(std::make_unique<LoginCommand>());
	dispatcher.registerCommand(std::make_unique<LogoutCommand>());
	dispatcher.registerCommand(std::make_unique<HelpCommand>());
	dispatcher.registerCommand(std::make_unique<CloseCommand>());
	dispatcher.registerCommand(std::make_unique<ViewProfileCommand>());
	dispatcher.registerCommand(std::make_unique<RegisterCommand>());
	dispatcher.registerCommand(std::make_unique<CreateProjectCommand>());
	dispatcher.registerCommand(std::make_unique<ArchiveProjectCommand>());
	dispatcher.registerCommand(std::make_unique<JoinProjectCommand>());
	dispatcher.registerCommand(std::make_unique<AddUserToProjectCommand>());
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
