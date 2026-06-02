#pragma once
#include "AppException.h"

class PermissionException : public AppException
{
public:
	explicit PermissionException(const std::string& message);
};
