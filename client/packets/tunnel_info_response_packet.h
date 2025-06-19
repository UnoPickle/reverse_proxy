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
#include "ipacket.h"

struct tunnel_info_respone_packet_struct
{
    reverse_proxy_packet_header header;
    uint16_t tunnel_port;
} __attribute__((packed));

class tunnel_info_response_packet : public ipacket
{
public:
    explicit tunnel_info_response_packet(uint16_t tunnel_port);
    ~tunnel_info_response_packet() override = default;

    uint16_t get_tunnel_port() const;

    [[nodiscard]] size_t packet_size() const override;
    [[nodiscard]] buffer serialize() const override;
    static tunnel_info_response_packet deserialize_headerless(const buffer& buffer);

private:
    uint16_t m_tunnel_port;
};
