#include "UserFactory.h"
#include "../users/Student.h"
#include "../users/TeachingAssistant.h"
#include "../users/Lecturer.h"
#include "../users/Administrator.h"
#include "../exceptions/ValidationException.h"
#include "../exceptions/StateException.h"

std::unique_ptr<User> UserFactory::createUser(const std::string& username, const std::string& password, Role role)
{
	switch (role)
	{
	case Role::Student:
		return std::make_unique<Student>(username, password);
	case Role::TeachingAssistant:
		return std::make_unique<TeachingAssistant>(username, password);
	case Role::Lecturer:
		return std::make_unique<Lecturer>(username, password);
	case Role::Administrator:
		throw StateException("Cannot create Administrator through factory.");
	default:
		throw ValidationException("Unknown role.");
	}
}

Role UserFactory::parseRole(const std::string& roleStr)
{
	std::string role = roleStr;
	for (char& c : role)
	{
		c = std::tolower(static_cast<unsigned char>(c));
	}

	if (role == "student" || role == "s")
	{
		return Role::Student;
	}
	if (role == "teachingassistant" || role == "ta")
	{
		return Role::TeachingAssistant;
	}
	if (role == "lecturer" || role == "l")
	{
		return Role::Lecturer;
	}
	if (role == "administrator" || role == "admin" || role == "a")
	{
		return Role::Administrator;
	}
	throw ValidationException("Unknown role: " + roleStr);
}
