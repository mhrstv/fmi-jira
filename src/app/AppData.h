#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "../users/User.h"
#include "../models/project/Project.h"

class AppData
{
	std::vector<std::unique_ptr<User>> users;
	std::vector<std::unique_ptr<Project>> projects;
	User* currentUser;
	bool running;

public:
	AppData();
	~AppData();

	bool isRunning() const;
	void stop();

	User* getCurrentUser() const;
	void setCurrentUser(User* user);

	void addUser(std::unique_ptr<User> user);
	User* findUser(const std::string& username) const;

	void addProject(std::unique_ptr<Project> project);
	Project* findProject(const std::string& name) const;
	const std::vector<std::unique_ptr<Project>>& getProjects() const;
	const std::vector<std::unique_ptr<User>>& getUsers() const;

	std::ostream& out();
};
