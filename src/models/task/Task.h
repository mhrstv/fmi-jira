#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "../../enums/TaskPriority.h"
#include "../../enums/TaskStatus.h"
#include "../../enums/TaskType.h"
#include "../../utils/Date.h"
#include "../comment/Comment.h"

class User;

class Task
{
	static size_t idGen;

	size_t id;
	std::string title;
	std::string description;
	TaskType type;
	TaskPriority priority;
	TaskStatus status;
	const User* assignee;
	Date deadline;
	int points;
	double grade;
	bool approved;
	std::vector<Comment> comments;
	std::vector<std::string> tags;
	std::vector<std::string> changeHistory;

public:
	Task(const std::string& title, const std::string& description, TaskType type, TaskPriority priority, const Date& deadline);

	size_t getId() const;
	std::string getFormattedId() const;
	const std::string& getTitle() const;
	const std::string& getDescription() const;
	TaskType getType() const;
	TaskPriority getPriority() const;
	TaskStatus getStatus() const;
	const User* getAssignee() const;
	const Date& getDeadline() const;
	int getPoints() const;
	double getGrade() const;
	bool isApproved() const;
	const std::vector<Comment>& getComments() const;
	const std::vector<std::string>& getTags() const;
	const std::vector<std::string>& getChangeHistory() const;

	void setTitle(const std::string& title);
	void setDescription(const std::string& description);
	void setPriority(TaskPriority priority);
	void setStatus(TaskStatus status);
	void setAssignee(const User* user);
	void setDeadline(const Date& deadline);
	void setPoints(int points);
	void setGrade(double grade);
	void setApproved(bool approved);

	void addComment(const Comment& comment);
	void addTag(const std::string& tag);

	static std::string typeToString(TaskType type);
	static std::string priorityToString(TaskPriority priority);
	static std::string statusToString(TaskStatus status);

	static TaskType parseType(const std::string& str);
	static TaskPriority parsePriority(const std::string& str);
	static TaskStatus parseStatus(const std::string& str);

	friend std::ostream& operator<<(std::ostream& os, const Task& task);
};