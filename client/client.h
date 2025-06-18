#pragma once
#include <cstdint>
#include <memory>
#include <bits/basic_string.h>

#include <format>
#include <thread>

#include "connections_manager.h"

#include "exceptions/winsock_exception.h"

namespace std
{
    class thread;
}

class client
{
public:
    client(const std::string& proxy_address, const uint16_t proxy_port, const uint16_t host_port);
    ~client();

private:
    SOCKET create_proxy_socket(const std::string& proxy_address, const uint16_t proxy_port);
    void start_proxy_socket_thread();
    void stop_proxy_socket_thread();

    void get_tunnel_info();

    void proxy_socket_thread_routine();

    uint16_t m_host_port;

    connections_manager m_connections_manager;
    SOCKET m_proxy_socket;

    uint16_t m_tunnel_port = 0;

    std::unique_ptr<std::thread> m_proxy_socket_thread = nullptr;
    bool m_proxy_socket_thread_running = true;
};
