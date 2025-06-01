#include "tunnel_info_response_packet.h"

#include <winsock2.h>

tunnel_info_response_packet::tunnel_info_response_packet(const uint16_t tunnel_port) : ipacket(reverse_proxy_packet_type::TUNNEL_INFO_REQUEST), m_tunnel_port(tunnel_port)
{
}

size_t tunnel_info_response_packet::packet_size() const
{
    return sizeof(tunnel_info_respone_packet_struct);
}

buffer tunnel_info_response_packet::serialize() const
{
    tunnel_info_respone_packet_struct packet{};
    packet.header.type = m_type;
    packet.tunnel_port = htons(m_tunnel_port);

    buffer buffer((uint8_t*)&packet, (uint8_t*)(&packet + 1));
    return buffer;
}
