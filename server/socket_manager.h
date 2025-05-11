#pragma once
#include <map>
#include <winsock2.h>
#include "buffer.h"
#include "guid.h"

class socket_manager
{
public:
    ~socket_manager();

    void send(const guid& socket_guid, const buffer& send_buffer);
    buffer recv(const guid& socket_guid, size_t max_read_size);

    guid accept(const guid& listener_guid);

    guid add_socket(SOCKET socket);
    void close_socket(const guid& guid);
private:
    SOCKET get_socket(const guid& socket_guid);

    std::map<guid, SOCKET> m_sockets;
};
