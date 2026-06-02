#pragma once
#include "User.h"

class Administrator : public User
{
public:
	Administrator(const std::string& username, const std::string& password);

	std::unique_ptr<User> clone() const override;

	void displayInfo(std::ostream& os) const override;
};