#pragma once
#include "server_exception.h"

class guid_creation_exception : public server_exception
{
public:
    explicit guid_creation_exception(const std::string& message);
    ~guid_creation_exception() noexcept override = default;
};
