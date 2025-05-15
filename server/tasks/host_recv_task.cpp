#include "host_recv_task.h"

#include "../socket_utils.h"
#include "../tunnel.h"
#include "../packets/ipacket.h"
#include "../packets/tunnel_info_packet.h"

host_recv_task::host_recv_task(socket_manager& socket_manager, tunnel_manager& tunnel_manager,
    const guid& tunnel_guid) : isocket_task(socket_manager), m_tunnel_manager(tunnel_manager), m_tunnel_guid(tunnel_guid), m_tunnel(m_tunnel_manager.get_tunnel(tunnel_guid))
{
}

void host_recv_task::complete()
{
    buffer buf = m_socket_manager.recv(m_tunnel.host(), sizeof(reverse_proxy_packet_header));

    reverse_proxy_packet_type type = static_cast<reverse_proxy_packet_type>(buf[0]);

    handle_packet(type);
}

bool host_recv_task::repeat()
{
    return m_socket_manager.socket_exists(m_tunnel.host());
}

void host_recv_task::handle_packet(const reverse_proxy_packet_type packet_type)
{
    switch (packet_type)
    {
    case reverse_proxy_packet_type::TUNNEL_INFO:

        break;
    case reverse_proxy_packet_type::CLIENT_CONNECTION:
        break;
    case reverse_proxy_packet_type::CLIENT_DISCONNECT:
        break;
    case reverse_proxy_packet_type::SERVER_DISCONNECT:
        break;
    case reverse_proxy_packet_type::COMMUNICATION:
        break;
    default: ;
    }
}

void host_recv_task::handle_tunnel_info() const
{
    const tunnel_info_packet packet(socket_utils::get_src_port(m_socket_manager.get_socket(m_tunnel.listener())));

    const buffer serialized_packet = packet.serialize();
    m_socket_manager.send(m_tunnel.host(), serialized_packet);
}
