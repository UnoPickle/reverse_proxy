#pragma once
#include <unordered_map>

#include "guid.h"

class socket_manager
{
public:
    void send();

private:
    std::unordered_map<guid, SOCKET>
};
