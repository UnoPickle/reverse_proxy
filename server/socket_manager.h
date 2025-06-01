#pragma once
#include <map>
#include <winsock2.h>
#include <bits/std_mutex.h>

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

    SOCKET get_socket(const guid& socket_guid);

    bool socket_exists(const guid& socket_guid);

private:
    std::mutex m_sockets_mutex;
    std::map<guid, SOCKET> m_sockets;
};
