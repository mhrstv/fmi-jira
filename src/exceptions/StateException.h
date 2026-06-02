#pragma once
#include "AppException.h"

class StateException : public AppException
{
public:
	explicit StateException(const std::string& message);
};
