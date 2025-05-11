#pragma once
#include "server_exception.h"

class winsock_exception : public server_exception
{
public:
    explicit winsock_exception(const std::string& message);
    ~winsock_exception() noexcept override = default;
};
