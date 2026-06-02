#pragma once
#include "AppException.h"

class DuplicateException : public AppException
{
public:
	explicit DuplicateException(const std::string& message);
};
