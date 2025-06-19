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
#include "../guid.h"

struct communication_packet_header_struct
{
    reverse_proxy_packet_header header;
    GUID client;
} __attribute__((packed));

class communication_packet : public ipacket
{
public:
    communication_packet(const guid& client, const buffer& packet);

    [[nodiscard]] size_t packet_size() const override;
    [[nodiscard]] buffer serialize() const override;
    static communication_packet deserialize(const buffer& packet);
    static communication_packet deserialize_headerless(const buffer& packet);

    [[nodiscard]] guid client_guid() const;
    [[nodiscard]] buffer payload_packet() const;

private:
    const guid m_client_guid;
    const buffer m_packet;
};
