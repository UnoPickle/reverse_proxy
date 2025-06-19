

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

enum class error_message_type : uint8_t
{
    INVALID_PACKET_TYPE = 0,
    INVALID_GUID,
};

struct error_response_packet_struct
{
    reverse_proxy_packet_header header;
    error_message_type error_message_type;
} __attribute__((packed));

class error_response_packet : public ipacket{
public:
    error_response_packet(const error_message_type& type);
    [[nodiscard]] size_t packet_size() const override;
    [[nodiscard]] buffer serialize() const override;
    ~error_response_packet() override = default;

private:
    error_message_type m_error_type;
};
