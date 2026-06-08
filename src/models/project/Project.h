#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "../../enums/ProjectStatus.h"

class User;
class Task;
class Stage;
class AppData;

class Project
{
	std::string name;
	std::string description;
	std::vector<User*> members;
	std::vector<std::unique_ptr<Task>> tasks;
	std::vector<std::unique_ptr<Stage>> stages;
	ProjectStatus status;

public:
	Project(const std::string& name, const std::string& description = "");
	~Project();

	const std::string& getName() const;
	const std::string& getDescription() const;
	ProjectStatus getStatus() const;
	const std::vector<User*>& getMembers() const;
	const std::vector<std::unique_ptr<Task>>& getTasks() const;
	const std::vector<std::unique_ptr<Stage>>& getStages() const;

	void save(std::ostream& os) const;
	static std::unique_ptr<Project> load(std::istream& is, const AppData& context, std::vector<std::pair<std::string, std::unique_ptr<Task>>>& allTasks);

	void setDescription(const std::string& description);

	void addMember(User* user);
	void removeMember(const std::string& username);
	bool hasMember(const std::string& username) const;
	User* findMember(const std::string& username) const;

	Task* addTask(std::unique_ptr<Task> task);
	Task* findTask(size_t taskId) const;
	
	// Finds a task using its full name (ex. 'PROJ-12')
	Task* findTaskByFormattedId(const std::string& formattedId) const;

	Stage* addStage(std::unique_ptr<Stage> stage);
	Stage* findStage(const std::string& stageName) const;

	// Changes project status to 'Finished'
	void finalize();
	
	// Changes project status to 'Finished' (archives it)
	void archive();

	static std::string statusToString(ProjectStatus status);

	friend std::ostream& operator<<(std::ostream& os, const Project& project);
};