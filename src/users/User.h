#pragma once
#include <string>
#include <iostream>
#include <memory>
#include "../enums/Role.h"

class User
{
	static size_t idGen;

	size_t id;
	std::string username;
	std::string password;
	Role role;

public:
	User(const std::string& username, const std::string& password, Role role);
	virtual ~User() = default;

	virtual std::unique_ptr<User> clone() const = 0;

	virtual void save(std::ostream& os) const;
	virtual void loadSubclass(std::istream& is) {}
	static std::unique_ptr<User> loadPoly(std::istream& is);

	size_t getId() const;
	const std::string& getUsername() const;
	Role getRole() const;

	bool checkPassword(const std::string& password) const;
	void changePassword(const std::string& oldPassword, const std::string& newPassword);

	std::string getRoleString() const;

	virtual void displayInfo(std::ostream& os) const;

	friend std::ostream& operator<<(std::ostream& os, const User& user);
};