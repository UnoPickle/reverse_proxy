#include "communication_packet.h"

#include <cstring>
#include <memory>

communication_packet::communication_packet(const guid& client, const buffer& packet) :
    ipacket(reverse_proxy_packet_type::COMMUNICATION), m_client_guid(client), m_packet(packet)
{
}

size_t communication_packet::packet_size() const
{
    return sizeof(communication_packet_header_struct) + m_packet.size();
}

buffer communication_packet::serialize() const
{
    std::unique_ptr<uint8_t[]> packet_buffer = std::make_unique<uint8_t[]>(packet_size());


    communication_packet_header_struct header{};

    header.header.type = m_type;
    header.header.length = packet_size() - sizeof(reverse_proxy_packet_header);
    memcpy(&header.client, m_client_guid.guid_ptr(), sizeof(GUID));


    std::memcpy(packet_buffer.get(), (uint8_t*)&header, sizeof(communication_packet_header_struct));
    memcpy(packet_buffer.get() + sizeof(header), m_packet.data(), m_packet.size());

    buffer buffer(packet_buffer.get(), packet_buffer.get() + packet_size());
    return buffer;
}

communication_packet communication_packet::deserialize(const buffer& packet)
{
    communication_packet_header_struct header{};
    memcpy((uint8_t*)&header, packet.data(), sizeof(communication_packet_header_struct));

    size_t packet_size = packet.size() - sizeof(communication_packet_header_struct);

    buffer payload_packet(packet.data() + sizeof(communication_packet_header_struct), packet.data() + packet_size);

    return {guid(header.client), payload_packet};
}

communication_packet communication_packet::deserialize_headerless(const buffer& packet)
{
    communication_packet_header_struct header{};
    size_t headerless_size = sizeof(communication_packet_header_struct) - sizeof(reverse_proxy_packet_header);
    memcpy(((uint8_t*)&header) + sizeof(reverse_proxy_packet_header), packet.data(), headerless_size);

    size_t payload_size = packet.size() - headerless_size;

    buffer payload_packet(packet.data() + headerless_size, packet.data() + headerless_size + payload_size);
    return {guid(header.client), payload_packet};
}

guid communication_packet::client_guid() const
{
    return m_client_guid;
}

buffer communication_packet::payload_packet() const
{
    return m_packet;
}
