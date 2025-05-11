#pragma once
#include "server_exception.h"

class tunnel_manager_exception : public server_exception
{
public:
    explicit tunnel_manager_exception(const std::string& message);
    ~tunnel_manager_exception() noexcept override = default;
};
