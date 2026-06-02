#pragma once
#include <memory>
#include <string>
#include "../enums/Role.h"
#include "../users/User.h"

class UserFactory
{
public:
	UserFactory() = delete;

	static std::unique_ptr<User> createUser(const std::string& username, const std::string& password, Role role);
	static Role parseRole(const std::string& role);
};
