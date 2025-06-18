#pragma once
#include "connection_exception.h"

class invalid_connection_exception : public connection_exception
{
public:
    invalid_connection_exception(const std::string& message);
    ~invalid_connection_exception() noexcept override = default;
};
