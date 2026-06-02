#pragma once
#include <stdexcept>
#include <string>

class AppException : public std::runtime_error
{
public:
	explicit AppException(const std::string& message);
	virtual ~AppException() = default;
};