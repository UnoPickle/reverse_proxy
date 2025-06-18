#pragma once
#include "client_exception.h"

class connection_exception : public client_exception
{
public:
    explicit connection_exception(const std::string& message);
    ~connection_exception() noexcept override = default;

};
