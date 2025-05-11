#pragma once
#include "server_exception.h"

class socket_manager_exception : public server_exception
{
public:
    explicit socket_manager_exception(const std::string& message);
    ~socket_manager_exception() noexcept override = default;
};
