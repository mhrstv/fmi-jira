#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "../../enums/TaskPriority.h"
#include "../../enums/TaskStatus.h"
#include "../../enums/TaskType.h"
#include "../../utils/Date.h"
#include "../comment/Comment.h"
class User;
class AppData;
#include "HistoryEntry.h"

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
	std::vector<HistoryEntry> changeHistory;

public:
	Task(const std::string& title, const std::string& description, TaskType type, TaskPriority priority);
	Task() = default;

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
	const std::vector<HistoryEntry>& getChangeHistory() const;

	void setTitle(const std::string& title, const User* changedBy, const Date& timestamp);
	void setDescription(const std::string& description, const User* changedBy, const Date& timestamp);
	void setPriority(TaskPriority priority, const User* changedBy, const Date& timestamp);
	void setStatus(TaskStatus status, const User* changedBy, const Date& timestamp);
	void setAssignee(const User* user, const User* changedBy, const Date& timestamp);
	void setDeadline(const Date& deadline, const User* changedBy, const Date& timestamp);
	void setPoints(int points, const User* changedBy, const Date& timestamp);
	void setGrade(double grade, const User* changedBy, const Date& timestamp);
	void setApproved(bool approved, const User* changedBy, const Date& timestamp);

	void addComment(const Comment& comment);
	void addTag(const std::string& tag, const User* changedBy, const Date& timestamp);

	void save(std::ostream& os) const;
	static std::unique_ptr<Task> load(std::istream& is, const AppData& context);

	static std::string typeToString(TaskType type);
	static std::string priorityToString(TaskPriority priority);
	static std::string statusToString(TaskStatus status);

	static TaskType parseType(const std::string& str);
	static TaskPriority parsePriority(const std::string& str);
	static TaskStatus parseStatus(const std::string& str);

	friend std::ostream& operator<<(std::ostream& os, const Task& task);
};