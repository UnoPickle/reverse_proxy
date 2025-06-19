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

struct client_disconnect_packet_struct
{
    reverse_proxy_packet_header header;
    GUID client_guid;
} __attribute__((packed));

class client_disconnect_packet : public ipacket
{
public:
    explicit client_disconnect_packet(const guid& client_guid);
    ~client_disconnect_packet() override = default;

    guid get_client_guid() const;

    [[nodiscard]] size_t packet_size() const override;
    [[nodiscard]] buffer serialize() const override;
    static client_disconnect_packet deserialize_headerless(const buffer& buffer);

private:
    guid m_client_guid;
};
