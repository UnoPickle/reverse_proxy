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

#pragma once
#include "../buffer.h"

enum class reverse_proxy_packet_type : uint8_t
{
    ERROR_RESPONSE = 0,
    TUNNEL_INFO_REQUEST,
    TUNNEL_INFO_RESPONSE,
    CLIENT_CONNECTION,
    CLIENT_DISCONNECT,
    COMMUNICATION,
};

struct reverse_proxy_packet_header
{
    reverse_proxy_packet_type type;
    uint64_t length;
} __attribute__((packed));

class ipacket
{
public:
    explicit ipacket(reverse_proxy_packet_type type);
    virtual ~ipacket() = default;

    [[nodiscard]] reverse_proxy_packet_type type() const;

    [[nodiscard]] virtual size_t packet_size() const = 0;
    [[nodiscard]] virtual buffer serialize() const = 0;


protected:
    const reverse_proxy_packet_type m_type;
};
