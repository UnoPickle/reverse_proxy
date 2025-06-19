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
#include <cstdint>
#include <memory>
#include <bits/basic_string.h>

#include <format>
#include <thread>

#include "connections_manager.h"

#include "exceptions/winsock_exception.h"
#include "packets/client_connection_packet.h"
#include "packets/client_disconnect_packet.h"
#include "packets/communication_packet.h"
#include "packets/error_response_packet.h"
#include "packets/ipacket.h"

namespace std
{
    class thread;
}

class client
{
public:
    client(const std::string& proxy_address, const uint16_t proxy_port, const uint16_t host_port);
    ~client();

    uint16_t get_tunnel_port() const;
private:
    SOCKET create_proxy_socket(const std::string& proxy_address, const uint16_t proxy_port);
    void start_proxy_socket_thread();
    void stop_proxy_socket_thread();

    void get_tunnel_info();

    void proxy_socket_thread_routine();
    void handle_packet(const reverse_proxy_packet_type type, const buffer& data);

    void handle_client_connection_packet(const client_connection_packet& packet);
    void handle_client_disconnect_packet(const client_disconnect_packet& packet);
    void handle_communication_packet(const communication_packet& packet);
    void handle_error_response_packet(const error_response_packet& packet);

    uint16_t m_host_port;

    connections_manager m_connections_manager;
    SOCKET m_proxy_socket;

    uint16_t m_tunnel_port = 0;

    std::unique_ptr<std::thread> m_proxy_socket_thread = nullptr;
    bool m_proxy_socket_thread_running = true;
};
