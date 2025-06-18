

#include "client_disconnect_packet.h"

client_disconnect_packet::client_disconnect_packet(const guid& client_guid) : ipacket(reverse_proxy_packet_type::CLIENT_DISCONNECT), m_client_guid(client_guid)
{
}

size_t client_disconnect_packet::packet_size() const
{
    return sizeof(client_disconnect_packet);
}

buffer client_disconnect_packet::serialize() const
{
    client_disconnect_packet_struct packet {};

    packet.header.type = m_type;
    packet.header.length = packet_size() - sizeof(reverse_proxy_packet_header);
    memcpy(&packet.client_guid, m_client_guid.guid_ptr(), sizeof(GUID));

    buffer buffer((uint8_t*)&packet, (uint8_t*)(&packet + 1));
    return buffer;
}
