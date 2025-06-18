#include "host_recv_task.h"

#include "../exceptions/socket_manager_exception.h"
#include "../exceptions/tunnel_exception.h"


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

        buffer buf = m_socket_manager.recv(tunnel->host(), sizeof(reverse_proxy_packet_header));
        reverse_proxy_packet_header header;

        memcpy(&header, buf.data(), sizeof(reverse_proxy_packet_header));


        buffer data;

        if (header.length > 0)
        {
            data = m_socket_manager.recv(tunnel->host(), header.length);
        }

        handle_packet(header.type, data);
    }
    catch (const winsock_nonblock_exception& e)
    {
        return;
    }catch (const winsock_exception& e)
    {
        try
        {
            m_tunnel_manager.close_tunnel(m_tunnel_guid);

        }catch (const socket_manager_exception& sock_manager_e)
        {
            return;
        }
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
        return m_socket_manager.socket_exists(tunnel->host());
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
    /*case reverse_proxy_packet_type::SERVER_DISCONNECT:
        m_tunnel_manager.close_tunnel(m_tunnel_guid);
        return;
        break;*/
    case reverse_proxy_packet_type::COMMUNICATION:
        handle_communication(communication_packet::deserialize(data));
        break;
    default: ;
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
    }
}
