#pragma once
#include <cstdint>
#include <winsock2.h>

namespace socket_utils
{
    void apply_socket_flags(SOCKET socket);
    uint16_t get_src_port(SOCKET socket);
};
