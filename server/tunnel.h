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
#include <vector>

#include "socket_manager.h"
#include "guid.h"


class tunnel
{
public:
    tunnel(socket_manager& socket_manager, const guid& host, const guid& listener);
    guid accept_client();
    void send_to(const guid& client, const buffer& buffer);
    buffer recv_from(const guid& client, size_t max_len);

    void delete_client(const guid& client);

    [[nodiscard]] guid host() const;
    [[nodiscard]] guid listener() const;
    [[nodiscard]] const std::vector<guid>& clients() const;

private:
    [[nodiscard]] bool client_in_tunnel(const guid& client);

    guid m_host;
    guid m_listener;

    std::mutex m_clients_mutex;
    std::vector<guid> m_clients;
    socket_manager& m_socket_manager;
};
