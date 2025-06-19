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

#include "host_client_con_task.h"

#include <iostream>

#include "client_recv_task.h"
#include "../task_manager.h"
#include "../exceptions/tunnel_manager_exception.h"
#include "../exceptions/winsock_nonblock_exception.h"
#include "../packets/client_connection_packet.h"

host_client_con_task::host_client_con_task(socket_manager& socket_manager, tunnel_manager& tunnel_manager,
                                           const tunnel_guid& tunnel_guid) : isocket_task(socket_manager),
                                                                             m_tunnel_manager(tunnel_manager), m_tunnel_guid(tunnel_guid)
{
}

void host_client_con_task::complete()
{
    try
    {
        const std::shared_ptr<tunnel> tunnel = m_tunnel_manager.get_tunnel(m_tunnel_guid);

        guid new_client_guid = tunnel->accept_client();

        g_task_manager.enqueue<client_recv_task>(m_socket_manager, m_tunnel_manager, m_tunnel_guid, new_client_guid);

        const client_connection_packet packet(new_client_guid);
        m_socket_manager.send(tunnel->host(), packet.serialize());

    }catch (const winsock_nonblock_exception& e)
    {

    }catch (const tunnel_manager_exception& e)
    {

    }
}

bool host_client_con_task::repeat()
{
    return m_tunnel_manager.tunnel_exists(m_tunnel_guid);
}
