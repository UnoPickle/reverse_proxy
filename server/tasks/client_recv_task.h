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
#include "isocket_task.h"
#include "../tunnel_manager.h"

constexpr size_t CLIENT_RECV_BUFFER_SIZE = 1024;

class client_recv_task : public isocket_task
{
public:
    client_recv_task(socket_manager& socket_manager, tunnel_manager& tunnel_manager, const tunnel_guid& tunnel_guid, const guid& client_guid);
    ~client_recv_task() override = default;
    void complete() override;
    bool repeat() override;

private:
    tunnel_manager& m_tunnel_manager;
    tunnel_guid m_tunnel_guid;
    guid m_client_guid;
};
