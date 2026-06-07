#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "../../utils/Date.h"
#include "../../enums/StageStatus.h"

class Task;

class Stage
{
	std::string name;
	Date startDate;
	Date endDate;
	std::vector<Task*> tasks;
	StageStatus status;

public:
	class Iterator {
		const std::vector<Task*>& tasksRef;
		size_t index;
	public:
		Iterator(const std::vector<Task*>& tasks) : tasksRef(tasks), index(0) {}
		bool hasNext() const { return index < tasksRef.size(); }
		Task* next() { return tasksRef[index++]; }
	};

	Stage(const std::string& name);

	const std::string& getName() const;
	const Date& getStartDate() const;
	const Date& getEndDate() const;
	StageStatus getStatus() const;
	const std::vector<Task*>& getTasks() const;
	Iterator getIterator() const { return Iterator(tasks); }

	void start(const Date& startDate);
	void finish(const Date& endDate);

	void addTask(Task* task);
	void removeTask(size_t taskId);
	bool containsTask(size_t taskId) const;

	int getTotalTaskCount() const;
	int getCompletedTaskCount() const;

	static std::string statusToString(StageStatus status);

	friend std::ostream& operator<<(std::ostream& os, const Stage& stage);
};