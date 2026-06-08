#include "AppData.h"
#include "../users/Administrator.h"
#include "../models/task/Task.h"
#include "../models/stage/Stage.h"

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
