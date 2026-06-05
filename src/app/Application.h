#pragma once
#include "AppData.h"
#include "CommandDispatcher.h"

class Application
{
	AppData data;
	CommandDispatcher dispatcher;

	void registerCommands();

public:
	Application();
	void run();
};
