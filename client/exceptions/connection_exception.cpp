#include "connection_exception.h"

connection_exception::connection_exception(const std::string& message) : client_exception(message)
{
}
