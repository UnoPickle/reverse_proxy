#include "server_exception.h"

server_exception::server_exception(const std::string& message) : m_message(message)
{
}

const char* server_exception::what() const noexcept
{
    return m_message.c_str();
}
