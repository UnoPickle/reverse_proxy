#pragma once
#include "client_exception.h"

class winsock_exception : public client_exception
{
public:
    explicit winsock_exception(const std::string& message);
    ~winsock_exception() noexcept override = default;
};
