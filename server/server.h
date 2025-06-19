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
#include <thread>

#include "socket_manager.h"
#include "tunnel_manager.h"


class server
{
public:
    server();
    ~server();

private:
    void start_config_listener_thread();
    void stop_config_listener_thread();

    void config_listener_thread_func();

    static SOCKET create_config_listener();
    static SOCKET create_tunnel_listener();

    guid m_config_listener;

    std::unique_ptr<std::thread> m_config_listener_thread;
    bool m_config_listener_running = true;

    socket_manager m_socket_manager;
    tunnel_manager m_tunnel_manager;
};
