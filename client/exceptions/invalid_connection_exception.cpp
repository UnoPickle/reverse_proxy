

#include "invalid_connection_exception.h"

invalid_connection_exception::invalid_connection_exception(const std::string& message) : connection_exception(message)
{
}
