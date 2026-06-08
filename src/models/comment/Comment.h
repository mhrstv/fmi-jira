#pragma once
#include <string>
#include <iostream>
#include "../../utils/Date.h"

class User;
class AppData;

class Comment
{
	const User* author;
	std::string content;
	Date creationDate;

public:
	Comment(const User* author, const std::string& content, const Date& date);

	const User* getAuthor() const;
	const std::string& getContent() const;
	const Date& getCreationDate() const;

	void save(std::ostream& os) const;
	static Comment load(std::istream& is, const AppData& context);

	friend std::ostream& operator<<(std::ostream& os, const Comment& comment);
};