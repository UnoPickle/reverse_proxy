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
    packet.header.length = packet_size() - sizeof(reverse_proxy_packet_header);

    buffer buffer((uint8_t*)&packet, (uint8_t*)(&packet + 1));
    return buffer;
}
