#pragma once
#include <unordered_map>
#include <winsock2.h>
#include "buffer.h"
#include "guid.h"

class socket_manager
{
public:
    void send(const guid& socket_guid, const buffer& send_buffer);

private:
    SOCKET get_socket(const guid& socket_guid);

    std::unordered_map<guid, SOCKET> m_sockets;
};
