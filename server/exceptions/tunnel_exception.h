#pragma once
#include "server_exception.h"

class tunnel_exception : public server_exception
{
public:
    explicit tunnel_exception(const std::string& message);
    ~tunnel_exception() noexcept override = default;
};
