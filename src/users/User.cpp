#include "User.h"
#include "../exceptions/ValidationException.h"
#include "../exceptions/AuthException.h"

size_t User::idGen = 1000;

User::User(const std::string& username, const std::string& password, Role role) : id(++idGen), username(username), password(password), role(role)
{
	if (username.empty())
	{
		throw ValidationException("Username cannot be empty.");
	}
	if (password.empty())
	{
		throw ValidationException("Password cannot be empty.");
	}
}

size_t User::getId() const
{
	return id;
}

const std::string& User::getUsername() const
{
	return username;
}

Role User::getRole() const
{
	return role;
}

bool User::checkPassword(const std::string& password) const
{
	return this->password == password;
}

void User::changePassword(const std::string& oldPassword, const std::string& newPassword)
{
	if (!checkPassword(oldPassword))
	{
		throw AuthException("Incorrect old password.");
	}
	if (newPassword.empty())
	{
		throw ValidationException("New password cannot be empty.");
	}
	this->password = newPassword;
}

std::string User::getRoleString() const
{
	switch (role)
	{
	case Role::Student:
		return "Student";
	case Role::TeachingAssistant:
		return "TeachingAssistant";
	case Role::Lecturer:
		return "Lecturer";
	case Role::Administrator:
		return "Administrator";
	default:
		return "Unknown";
	}
}

void User::displayInfo(std::ostream& os) const
{
	os << "ID: " << id << "\n"
		<< "Username: " << username << "\n"
		<< "Role: " << getRoleString() << "\n";
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
	user.displayInfo(os);
	return os;
}