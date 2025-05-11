#pragma once
#include <cstdint>

enum class packet_type : uint8_t
{
    CLIENT_CONNECTION = 0,
    CLIENT_DISCONNECT,
    SERVER_DISCONNECT,
    COMMUNICATION,
};