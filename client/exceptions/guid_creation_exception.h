#pragma once
#include "client_exception.h"

class guid_creation_exception : public client_exception
{
public:
    explicit guid_creation_exception(const std::string& message);
    ~guid_creation_exception() noexcept override = default;
};
