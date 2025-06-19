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

    SOCKET get_socket(const guid& socket_guid);

    bool socket_exists(const guid& socket_guid);

    void close_socket(const guid& guid);

private:
    std::mutex m_sockets_mutex;
    std::map<guid, SOCKET> m_sockets;
};
