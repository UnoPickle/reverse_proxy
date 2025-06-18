#pragma once
#include <cstdint>
#include <map>

#include <winsock2.h>

#include "buffer.h"
#include "guid.h"

class connections_manager
{
public:
    SOCKET create_connection(const guid& client_guid, const uint16_t host_port);
    SOCKET get_socket(const guid& guid);
    void close_connection(const guid& guid);

    bool connection_exists(const guid& guid) const;

    int send_to(const guid& client_guid, const buffer& buffer);
    buffer recv_from(const guid& client_guid, size_t max_read_size);
private:
    std::map<guid, SOCKET> m_connections;
};
