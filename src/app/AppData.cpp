#include "AppData.h"
#include "../users/Administrator.h"
#include "../factories/UserFactory.h"
#include "../models/task/Task.h"
#include "../models/stage/Stage.h"
#include "../utils/DataStream.h"
#include <fstream>
#include <stdexcept>

AppData::AppData() : currentUser(nullptr), running(true) { }

AppData::~AppData() = default;

bool AppData::isRunning() const
{
	return running;
}

void AppData::stop()
{
	running = false;
}

User* AppData::getCurrentUser() const
{
	return currentUser;
}

void AppData::setCurrentUser(User* user)
{
	currentUser = user;
}

void AppData::addUser(std::unique_ptr<User> user)
{
	users.push_back(std::move(user));
}

User* AppData::findUser(const std::string& username) const
{
	if (Administrator::getInstance().getUsername() == username)
	{
		return &Administrator::getInstance();
	}
	for (const auto& user : users)
	{
		if (user->getUsername() == username)
		{
			return user.get();
		}
	}
	return nullptr;
}

void AppData::addProject(std::unique_ptr<Project> project)
{
	projects.push_back(std::move(project));
}

Project* AppData::findProject(const std::string& name) const
{
	for (const auto& project : projects)
	{
		if (project->getName() == name)
		{
			return project.get();
		}
	}
	return nullptr;
}

const std::vector<std::unique_ptr<Project>>& AppData::getProjects() const
{
	return projects;
}

const std::vector<std::unique_ptr<User>>& AppData::getUsers() const
{
	return users;
}

std::istream& AppData::is()
{
	return std::cin;
}

std::ostream& AppData::os()
{
	return std::cout;
}

void AppData::save() const
{
	std::ofstream usersOut("users.txt");
	if (usersOut.is_open())
	{
		DataStream::writeSizeT(usersOut, users.size());
		for (const auto& user : users)
		{
			user->save(usersOut);
		}
	}

	std::ofstream projectsOut("projects.txt");
	if (projectsOut.is_open())
	{
		DataStream::writeSizeT(projectsOut, projects.size());
		for (const auto& project : projects)
		{
			project->save(projectsOut);
		}
	}

	std::ofstream tasksOut("tasks.txt");
	if (tasksOut.is_open())
	{
		size_t totalTasks = 0;
		for (const auto& project : projects)
		{
			totalTasks += project->getTasks().size();
		}
		
		DataStream::writeSizeT(tasksOut, totalTasks);
		for (const auto& project : projects)
		{
			for (const auto& task : project->getTasks())
			{
				DataStream::writeString(tasksOut, project->getName());
				task->save(tasksOut);
			}
		}
	}
}

void AppData::load()
{
	users.clear();
	projects.clear();
	currentUser = nullptr;

	std::ifstream usersIn("users.txt");
	if (usersIn.is_open())
	{
		size_t usersCount = DataStream::readSizeT(usersIn);
		for (size_t i = 0; i < usersCount; i++)
		{
			auto user = User::loadPoly(usersIn);
			users.push_back(std::move(user));
		}
	}

	std::vector<std::pair<std::string, std::unique_ptr<Task>>> loadedTasks;
	std::ifstream tasksIn("tasks.txt");
	if (tasksIn.is_open())
	{
		size_t tasksCount = DataStream::readSizeT(tasksIn);
		for (size_t i = 0; i < tasksCount; i++)
		{
			std::string projectName = DataStream::readString(tasksIn);
			auto task = Task::load(tasksIn, *this);
			loadedTasks.push_back(std::make_pair(projectName, std::move(task)));
		}
	}

	std::ifstream projectsIn("projects.txt");
	if (projectsIn.is_open())
	{
		size_t projectsCount = DataStream::readSizeT(projectsIn);
		for (size_t i = 0; i < projectsCount; i++)
		{
			projects.push_back(Project::load(projectsIn, *this, loadedTasks));
		}
	}
}