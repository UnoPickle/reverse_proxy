#pragma once
#include "client_exception.h"

class tunnel_info_exception : public client_exception
{
public:
    explicit tunnel_info_exception(const std::string& message);
    ~tunnel_info_exception() noexcept override = default;
};
