#include "ValidationException.h"

ValidationException::ValidationException(const std::string& message) : AppException(message) { }
