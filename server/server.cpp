#include "server.h"

#include "config.h"
#include "socket_utils.h"
#include "task_manager.h"
#include "exceptions/winsock_exception.h"
#include "tasks/client_con_task.h"
#include "tasks/host_recv_task.h"

server::server() : m_tunnel_manager(m_socket_manager)
{
    m_config_listener = m_socket_manager.add_socket(create_config_listener());

    start_config_listener_thread();
}

server::~server()
{
    stop_config_listener_thread();
}

void server::start_config_listener_thread()
{
    if (m_config_listener_thread)
    {
        return;
    }

    m_config_listener_running = true;

    m_config_listener_thread = std::make_unique<std::thread>(&server::config_listener_thread_func, this);
}

void server::stop_config_listener_thread()
{
    if (!m_config_listener_thread)
    {
        return;
    }

    m_config_listener_running = false;

    pthread_kill(m_config_listener_thread->native_handle(), SIGINT);
}

void server::config_listener_thread_func()
{
    while (m_config_listener_running)
    {
        guid new_server_guid = m_socket_manager.accept(m_config_listener);

        const SOCKET new_server_socket = m_socket_manager.get_socket(new_server_guid);
        socket_utils::apply_socket_flags(new_server_socket);

        const SOCKET new_tunnel_listener = create_tunnel_listener();
        socket_utils::apply_socket_flags(new_tunnel_listener);


        guid new_tunnel_listener_guid = m_socket_manager.add_socket(new_tunnel_listener);

        tunnel_guid new_tunnel_guid = m_tunnel_manager.create_tunnel(new_server_guid, new_tunnel_listener_guid);

        g_task_manager.enqueue<host_recv_task>(m_socket_manager, new_server_guid);
        g_task_manager.enqueue<client_con_task>(m_socket_manager, m_tunnel_manager, new_tunnel_guid);
    }
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
    server_address.sin_port = htons(config::config_port);

    if (bind(listener_socket, (sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
    {
        throw winsock_exception("failed to bind config listener socket");
    }

    listen(listener_socket, SOMAXCONN);

    return listener_socket;
}

SOCKET server::create_tunnel_listener()
{
    const SOCKET listener_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listener_socket == INVALID_SOCKET)
    {
        throw winsock_exception("failed to create tunnel listener socket");
    }

    sockaddr_in server_address = {};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(0);

    if (bind(listener_socket, (sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
    {
        throw winsock_exception("failed to bind config listener socket");
    }

    listen(listener_socket, SOMAXCONN);

    return listener_socket;
}
