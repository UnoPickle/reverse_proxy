#include "tunnel_info_request_packet.h"

tunnel_info_request_packet::tunnel_info_request_packet() : ipacket(reverse_proxy_packet_type::TUNNEL_INFO_REQUEST)
{
}

size_t tunnel_info_request_packet::packet_size() const
{
    return sizeof(tunnel_info_request_packet_struct);
}

buffer tunnel_info_request_packet::serialize() const
{
    tunnel_info_request_packet_struct packet;
    packet.header.type = m_type;
    packet.header.length = packet_size() - sizeof(reverse_proxy_packet_type);

    buffer buffer((uint8_t*)&packet, (uint8_t*)(&packet + 1));
    return buffer;
}
