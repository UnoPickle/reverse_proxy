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
