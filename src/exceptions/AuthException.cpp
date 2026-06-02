#include "AuthException.h"

AuthException::AuthException(const std::string& message) : AppException(message) { }
