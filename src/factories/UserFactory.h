#pragma once
#include <memory>
#include <string>
#include "../enums/Role.h"
#include "../users/User.h"

class UserFactory
{
public:
	UserFactory() = delete;

	// Creates a user object of the given role (Student, Technical Assistant, Lecturer)
	static std::unique_ptr<User> createUser(const std::string& username, const std::string& password, Role role);
	
	// Converts text like "admin" into a Role
	static Role parseRole(const std::string& role);
};
