#include "Administrator.h"

Administrator::Administrator(const std::string& username, const std::string& password) : User(username, password, Role::Administrator) { }

std::unique_ptr<User> Administrator::clone() const
{
	return std::make_unique<Administrator>(*this);
}

void Administrator::displayInfo(std::ostream& os) const
{
	User::displayInfo(os);
	os << "(System Administrator)\n";
}