#pragma once
#include <string>
#include <iostream>
#include "../../utils/Date.h"

class User;

class HistoryEntry
{
	const User* changedBy;
	std::string field;
	std::string oldValue;
	std::string newValue;
	Date timestamp;

public:
	HistoryEntry(const User* changedBy, const std::string& field, const std::string& oldValue, const std::string& newValue, const Date& timestamp);

	const User* getChangedBy() const;
	const std::string& getField() const;
	const std::string& getOldValue() const;
	const std::string& getNewValue() const;
	const Date& getTimestamp() const;

	friend std::ostream& operator<<(std::ostream& os, const HistoryEntry& entry);
};
