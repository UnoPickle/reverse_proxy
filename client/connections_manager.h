// Simple Reverse Proxy - A simple reverse proxy that allows remote
//     clients to connect to a local host
//     Copyright (C) 2025  Hagaib
//
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.

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
