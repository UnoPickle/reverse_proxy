#include "client_connection_packet.h"

#include <cstring>
#include <memory>

client_connection_packet::client_connection_packet(const guid& client_guid) : ipacket(reverse_proxy_packet_type::CLIENT_CONNECTION),
                                                                              m_client_guid(client_guid)
{
}

guid client_connection_packet::client_guid() const
{
    return m_client_guid;
}

size_t client_connection_packet::packet_size() const
{
    return sizeof(client_connection_packet_struct);
}

buffer client_connection_packet::serialize() const
{
    client_connection_packet_struct packet {};

    packet.header.type = m_type;
    packet.header.length = packet_size() - sizeof(reverse_proxy_packet_header);
    memcpy(&packet.client_guid, m_client_guid.guid_ptr(), sizeof(GUID));

    // Addition is calculated based on the type of the pointer so +1
    // just means get the address that is the current one plus a whole struct
    buffer buffer((uint8_t*)&packet, (uint8_t*)(&packet + 1));
    return buffer;
}

client_connection_packet client_connection_packet::deserialize_headerless(const buffer& buffer)
{
    client_connection_packet_struct packet{};
    std::memcpy(((uint8_t*)&packet) + sizeof(reverse_proxy_packet_header), buffer.data(), buffer.size());

    return client_connection_packet(guid(packet.client_guid));
}
