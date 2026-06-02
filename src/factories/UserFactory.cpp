#include "UserFactory.h"
#include "../users/Student.h"
#include "../users/TeachingAssistant.h"
#include "../users/Lecturer.h"
#include "../users/Administrator.h"
#include "../exceptions/ValidationException.h"

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
		return std::make_unique<Administrator>(username, password);
	default:
		throw ValidationException("Unknown role.");
	}
}

Role UserFactory::parseRole(const std::string& role)
{
	if (role == "Student")
	{
		return Role::Student;
	}
	if (role == "TeachingAssistant")
	{
		return Role::TeachingAssistant;
	}
	if (role == "Lecturer")
	{
		return Role::Lecturer;
	}
	if (role == "Administrator")
	{
		return Role::Administrator;
	}
	throw ValidationException("Unknown role: " + role);
}
