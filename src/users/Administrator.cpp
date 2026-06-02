#include "Administrator.h"
#include "../exceptions/StateException.h"

Administrator::Administrator(const std::string& username, const std::string& password) : User(username, password, Role::Administrator) { }

Administrator& Administrator::getInstance()
{
	static Administrator instance("admin", "admin");
	return instance;
}

std::unique_ptr<User> Administrator::clone() const
{
	throw StateException("Cannot clone Administrator.");
}

void Administrator::displayInfo(std::ostream& os) const
{
	User::displayInfo(os);
	os << "(System Administrator)\n";
}