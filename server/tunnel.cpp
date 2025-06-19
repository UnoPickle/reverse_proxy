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

#include "tunnel.h"

#include <algorithm>
#include <mutex>

#include "exceptions/tunnel_exception.h"


tunnel::tunnel(socket_manager& socket_manager, const guid& host, const guid& listener): m_host(host),
    m_listener(listener), m_socket_manager(socket_manager)

{
}

guid tunnel::accept_client()
{
    guid guid = m_socket_manager.accept(m_listener);

    std::unique_lock lock(m_clients_mutex);
    m_clients.push_back(guid);

    return guid;
}

void tunnel::send_to(const guid& client, const buffer& buffer)
{
    if (!client_in_tunnel(client))
    {
        throw tunnel_exception("client not found in tunnel");
    }

    m_socket_manager.send(client, buffer);
}

buffer tunnel::recv_from(const guid& client, const size_t max_len)
{
    if (!client_in_tunnel(client))
    {
        throw tunnel_exception("client not found in tunnel");
    }

    return m_socket_manager.recv(client, max_len);
}


void tunnel::delete_client(const guid& client)
{
    std::unique_lock lock(m_clients_mutex);

    const auto it = std::find(m_clients.begin(), m_clients.end(), client);

    if (it == m_clients.end())
    {
        throw tunnel_exception("client not found in tunnel");
    }

    m_clients.erase(it);
}

guid tunnel::host() const
{
    return m_host;
}

guid tunnel::listener() const
{
    return m_listener;
}

const std::vector<guid>& tunnel::clients() const
{
    return m_clients;
}

bool tunnel::client_in_tunnel(const guid& client)
{
    std::unique_lock lock(m_clients_mutex);
    return std::ranges::find(m_clients, client) != m_clients.end();
}
