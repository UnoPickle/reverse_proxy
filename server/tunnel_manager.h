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

#include "tunnel.h"
#include "guid.h"

using tunnel_guid = guid;

class tunnel_manager
{
public:
    explicit tunnel_manager(socket_manager& socket_manager);

    tunnel_guid create_tunnel(const guid& host_guid, const guid& listener_guid);
    std::shared_ptr<tunnel> get_tunnel(const tunnel_guid& guid);

    void close_tunnel(const tunnel_guid& tunnel_guid);

    bool tunnel_exists(const tunnel_guid& tunnel_guid);

private:
    socket_manager& m_socket_manager;

    std::mutex m_tunnels_mutex;
    std::map<tunnel_guid, std::shared_ptr<tunnel>> m_tunnels;
};
