

#include "client_exception.h"

client_exception::client_exception(const std::string& message) : m_message(message)
{
}

const char* client_exception::what() const noexcept
{
    return m_message.c_str();
}
