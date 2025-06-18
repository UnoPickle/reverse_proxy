#pragma once
#include "client_exception.h"

class winsock_nonblock_exception : public client_exception
{
public:
    explicit winsock_nonblock_exception(const std::string& message);
    ~winsock_nonblock_exception() noexcept override = default;
};
