#pragma once
#include "User.h"

class Administrator : public User
{
	Administrator(const std::string& username, const std::string& password);

public:
	Administrator(const Administrator&) = delete;
	Administrator& operator=(const Administrator&) = delete;
	Administrator(Administrator&&) = delete;
	Administrator& operator=(Administrator&&) = delete;

	static Administrator& getInstance();

	std::unique_ptr<User> clone() const override;

	void displayInfo(std::ostream& os) const override;
};