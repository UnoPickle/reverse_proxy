#include "error_response_packet.h"

#include <cstring>

error_response_packet::error_response_packet(const error_message_type& type) :
    ipacket(reverse_proxy_packet_type::ERROR_RESPONSE), m_error_type(type)
{
}

error_message_type error_response_packet::get_error_type() const
{
    return m_error_type;
}

size_t error_response_packet::packet_size() const
{
    return sizeof(error_response_packet_struct) - sizeof(reverse_proxy_packet_header);
}

buffer error_response_packet::serialize() const
{
    error_response_packet_struct packet;

    packet.header.type = m_type;
    packet.header.length = packet_size() - sizeof(reverse_proxy_packet_header);

    packet.error_message_type = m_error_type;

    buffer buffer((uint8_t*)&packet, (uint8_t*)(&packet + 1));
    return buffer;
}

error_response_packet error_response_packet::deserialize_headerless(const buffer& buffer)
{
    error_response_packet_struct packet{};
    std::memcpy(((uint8_t*)&packet) + sizeof(reverse_proxy_packet_header), buffer.data(), buffer.size());

    return error_response_packet(packet.error_message_type);
}
