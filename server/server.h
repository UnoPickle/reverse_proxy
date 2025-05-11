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
