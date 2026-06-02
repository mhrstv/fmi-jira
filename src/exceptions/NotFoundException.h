#pragma once
#include "AppException.h"

class NotFoundException : public AppException
{
public:
	explicit NotFoundException(const std::string& message);
};
