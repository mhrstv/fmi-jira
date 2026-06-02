#pragma once
#include "AppException.h"

class ValidationException : public AppException
{
public:
	explicit ValidationException(const std::string& message);
};
