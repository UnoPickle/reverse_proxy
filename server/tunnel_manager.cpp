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

#include "tunnel_manager.h"

#include <mutex>

#include "exceptions/socket_manager_exception.h"
#include "exceptions/tunnel_manager_exception.h"

tunnel_manager::tunnel_manager(socket_manager& socket_manager) : m_socket_manager(socket_manager)
{
}

tunnel_guid tunnel_manager::create_tunnel(const guid& host_guid, const guid& listener_guid)
{
    tunnel_guid new_guid = guid::generate_guid();

    std::unique_lock lock(m_tunnels_mutex);
    m_tunnels.emplace(new_guid, std::make_shared<tunnel>(m_socket_manager, host_guid, listener_guid));

    return new_guid;
}

std::shared_ptr<tunnel> tunnel_manager::get_tunnel(const tunnel_guid& guid)
{
    std::unique_lock lock(m_tunnels_mutex);
    const auto it = m_tunnels.find(guid);

    if (it == m_tunnels.end())
    {
        throw tunnel_manager_exception("could not find tunnel with given tunnel guid");
    }

    return it->second;
}

void tunnel_manager::close_tunnel(const tunnel_guid& tunnel_guid)
{
    std::unique_lock lock(m_tunnels_mutex);
    const auto it = m_tunnels.find(tunnel_guid);

    if (it == m_tunnels.end())
    {
        throw tunnel_manager_exception("could not find tunnel with given tunnel guid");
    }

    const std::shared_ptr<tunnel> tunnel = it->second;


    if (m_socket_manager.socket_exists(tunnel->host()))
    {
        m_socket_manager.close_socket(tunnel->host());
    }

    if (m_socket_manager.socket_exists(tunnel->listener()))
    {
        m_socket_manager.close_socket(tunnel->listener());
    }

    for (guid client_guid : tunnel->clients())
    {
        if (m_socket_manager.socket_exists(client_guid))
        {
            m_socket_manager.close_socket(client_guid);
        }
    }


    m_tunnels.erase(it);
}

bool tunnel_manager::tunnel_exists(const tunnel_guid& tunnel_guid)
{
    std::unique_lock lock(m_tunnels_mutex);
    const auto it = m_tunnels.find(tunnel_guid);

    return it != m_tunnels.end();
}
