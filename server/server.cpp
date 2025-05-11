#include "server.h"

#include "config.h"
#include "socket_utils.h"
#include "exceptions/winsock_exception.h"

server::server() : m_tunnel_manager(m_socket_manager)
{
    m_config_listener = m_socket_manager.add_socket(create_config_listener());

    
}

server::~server()
{
}

SOCKET server::create_config_listener()
{
    const SOCKET listener_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listener_socket == INVALID_SOCKET)
    {
        throw winsock_exception("failed to create config listener socket");
    }

    sockaddr_in server_address = {};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = config::config_port;

    if (bind(listener_socket, (sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
    {
        throw winsock_exception("failed to bind config listener socket");
    }

    listen(listener_socket, SOMAXCONN);

    return listener_socket;
}
