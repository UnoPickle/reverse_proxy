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

struct tunnel_info_request_packet_struct
{
    reverse_proxy_packet_header header;
} __attribute__((packed));

class tunnel_info_request_packet : public ipacket
{
public:
    tunnel_info_request_packet();
    ~tunnel_info_request_packet() override = default;
    [[nodiscard]] size_t packet_size() const override;
    [[nodiscard]] buffer serialize() const override;
};
