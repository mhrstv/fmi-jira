#pragma once
#include "AppException.h"

class AuthException : public AppException
{
public:
	explicit AuthException(const std::string& message);
};
