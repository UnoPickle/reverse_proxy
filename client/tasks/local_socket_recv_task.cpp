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

#include "local_socket_recv_task.h"

#include "../socket_utils.h"
#include "../exceptions/winsock_exception.h"
#include "../exceptions/winsock_nonblock_exception.h"
#include "../packets/client_disconnect_packet.h"
#include "../packets/communication_packet.h"

local_socket_recv_task::local_socket_recv_task(connections_manager& connections_manager, const SOCKET proxy_socket,
                                               const guid& client_guid) :
    m_connections_manager(connections_manager), m_proxy_socket(proxy_socket), m_client_guid(client_guid)
{
}


void local_socket_recv_task::complete()
{
    try
    {
        buffer packet = m_connections_manager.recv_from(m_client_guid, LOCAL_SOCKET_RECV_BUFFER_SIZE);

        const communication_packet communication_packet(m_client_guid, packet);
        socket_utils::send(m_proxy_socket, communication_packet.serialize());
    }catch (const winsock_exception& e)
    {
        client_disconnect_packet client_disconnect_packet(m_client_guid);
        socket_utils::send(m_proxy_socket, client_disconnect_packet.serialize());

        m_connections_manager.close_connection(m_client_guid);
    }
    catch (const winsock_nonblock_exception& e)
    {
    }
}

bool local_socket_recv_task::repeat()
{
    return m_connections_manager.connection_exists(m_client_guid);
}
