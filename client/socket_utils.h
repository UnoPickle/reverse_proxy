#pragma once

#include <winsock2.h>
#include "buffer.h"

namespace socket_utils
{
    int send(SOCKET socket, const buffer& buffer);
    buffer recv(SOCKET socket, const size_t max_read_size);
}
