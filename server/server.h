#pragma once
#include "socket_manager.h"
#include "tunnel_manager.h"


class server
{
public:
    server();
    ~server();

private:
    static SOCKET create_config_listener();

    guid m_config_listener;

    socket_manager m_socket_manager;
    tunnel_manager m_tunnel_manager;
};
