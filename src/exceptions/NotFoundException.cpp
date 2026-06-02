#include "NotFoundException.h"

NotFoundException::NotFoundException(const std::string& message) : AppException(message) { }
