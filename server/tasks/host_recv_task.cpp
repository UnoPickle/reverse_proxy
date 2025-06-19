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

#include "host_recv_task.h"

#include <iostream>

#include "../exceptions/tunnel_manager_exception.h"


host_recv_task::host_recv_task(socket_manager& socket_manager, tunnel_manager& tunnel_manager,
                               const guid& tunnel_guid) : isocket_task(socket_manager),
                                                          m_tunnel_manager(tunnel_manager), m_tunnel_guid(tunnel_guid)
{
}

void host_recv_task::complete()
{
    try
    {
        const std::shared_ptr<tunnel> tunnel = m_tunnel_manager.get_tunnel(m_tunnel_guid);

        if (m_recv_task == nullptr)
        {
            m_recv_task = std::make_shared<recv_size_packet_task>(m_socket_manager, tunnel->host(),
                                                                  sizeof(reverse_proxy_packet_header));

            g_task_manager.enqueue(m_recv_task);
            return;
        }

        if (m_recv_task->repeat() == true)
        {
            return;
        }

        buffer received_packet = m_recv_task->get_data();

        if (!m_receiving_data)
        {
            reverse_proxy_packet_header header;

            memcpy(&header, received_packet.data(), sizeof(reverse_proxy_packet_header));

            m_receiving_data = true;
            m_processing_packet_type = header.type;

            size_t data_length = header.length;
            m_recv_task = std::make_shared<recv_size_packet_task>(m_socket_manager, tunnel->host(), data_length);

            g_task_manager.enqueue(m_recv_task);
            return;
        }

        m_receiving_data = false;
        m_recv_task = nullptr;

        handle_packet(m_processing_packet_type, received_packet);
    }
    catch (const winsock_nonblock_exception& e)
    {
        return;
    }catch (const winsock_exception& e)
    {
        m_tunnel_manager.close_tunnel(m_tunnel_guid);
        return;
    }catch (const socket_manager_exception& e)
    {
        return;
    }
}

bool host_recv_task::repeat()
{
    try
    {
        const std::shared_ptr<tunnel> tunnel = m_tunnel_manager.get_tunnel(m_tunnel_guid);
        bool host_exists = m_socket_manager.socket_exists(tunnel->host());
        return host_exists;
    }
    catch (const std::exception& e)
    {
        return false;
    }
}

void host_recv_task::handle_packet(const reverse_proxy_packet_type packet_type, const buffer& data)
{
    switch (packet_type)
    {
    case reverse_proxy_packet_type::TUNNEL_INFO_REQUEST:
        handle_tunnel_info();
        break;
    case reverse_proxy_packet_type::COMMUNICATION:
        {
            handle_communication(communication_packet::deserialize_headerless(data));
        }
        break;
    case reverse_proxy_packet_type::CLIENT_DISCONNECT:
        {
            handle_client_disconnect(client_disconnect_packet::deserialize_headerless(data));
        }
        break;
    default:
        handle_unknown_packet();;
    }
}


void host_recv_task::handle_tunnel_info() const
{
    const std::shared_ptr<tunnel> tunnel = m_tunnel_manager.get_tunnel(m_tunnel_guid);

    const tunnel_info_response_packet packet(
        socket_utils::get_src_port(m_socket_manager.get_socket(tunnel->listener())));

    const buffer serialized_packet = packet.serialize();
    m_socket_manager.send(tunnel->host(), serialized_packet);
}

void host_recv_task::handle_communication(const communication_packet& data) const
{
    const std::shared_ptr<tunnel> tunnel = m_tunnel_manager.get_tunnel(m_tunnel_guid);

    try
    {
        tunnel->send_to(data.client_guid(), data.payload_packet());
    }
    catch (tunnel_exception& e)
    {
    }catch (const socket_manager_exception& e)
    {
        const error_response_packet error(error_message_type::INVALID_GUID);
        m_socket_manager.send(tunnel->host(), error.serialize());
    }
}

void host_recv_task::handle_client_disconnect(const client_disconnect_packet& data) const
{
    try
    {
        const std::shared_ptr<tunnel> tunnel = m_tunnel_manager.get_tunnel(m_tunnel_guid);

       tunnel->delete_client(data.client_guid());
        m_socket_manager.close_socket(data.client_guid());
    }catch (const tunnel_manager_exception& e)
    {
    }
}

void host_recv_task::handle_unknown_packet()
{
    try
    {
        const std::shared_ptr<tunnel> tunnel = m_tunnel_manager.get_tunnel(m_tunnel_guid);

        const error_response_packet error(error_message_type::INVALID_PACKET_TYPE);
        m_socket_manager.send(tunnel->host(), error.serialize());
    }
    catch (const socket_manager_exception& e)
    {
    }catch (const tunnel_manager_exception& e)
    {
    }
}
