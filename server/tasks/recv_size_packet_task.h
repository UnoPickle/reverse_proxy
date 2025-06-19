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
#include <memory>

#include "itask.h"
#include "../buffer.h"
#include "../guid.h"
#include "../socket_manager.h"
#include "../exceptions/winsock_exception.h"

class recv_size_packet_task : public itask
{
public:
    recv_size_packet_task(socket_manager& socket_manager, const guid& socket_guid, const size_t recv_size);
    ~recv_size_packet_task() override = default;
    void complete() override;
    bool repeat() override;

    buffer get_data();

private:
    socket_manager& m_socket_manager;
    guid m_socket_guid;
    size_t m_recv_size;

    size_t m_currently_received = 0;
    buffer m_buffer;
    std::shared_ptr<winsock_exception> m_winsock_exception = nullptr;
};
