#include "client.h"

#include <cstring>
#include <iostream>

#include "socket_utils.h"
#include "task_manager.h"
#include "exceptions/error_response_exception.h"
#include "exceptions/tunnel_info_exception.h"
#include "exceptions/winsock_nonblock_exception.h"
#include "packets/ipacket.h"
#include "packets/tunnel_info_request_packet.h"
#include "packets/tunnel_info_response_packet.h"
#include "tasks/local_socket_recv_task.h"

client::client(const std::string& proxy_address, const uint16_t proxy_port, const uint16_t host_port) : m_host_port(
    host_port)
{
    m_proxy_socket = create_proxy_socket(proxy_address, proxy_port);
    get_tunnel_info();

    start_proxy_socket_thread();
}

client::~client()
{
    g_task_manager.force_stop();
    closesocket(m_proxy_socket);
    stop_proxy_socket_thread();
}

uint16_t client::get_tunnel_port() const
{
    return m_tunnel_port;
}

SOCKET client::create_proxy_socket(const std::string& proxy_address, const uint16_t proxy_port)
{
    SOCKET proxy_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (proxy_socket == INVALID_SOCKET)
    {
        throw winsock_exception("couldn't create proxy socket");
    }


    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(proxy_port);
    address.sin_addr.s_addr = inet_addr(proxy_address.c_str());

    if (connect(proxy_socket, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR)
    {
        throw winsock_exception(std::format("couldn't connect to proxy at {}:{}", proxy_address,
                                            std::to_string(proxy_port)));
    }


    return proxy_socket;
}

void client::start_proxy_socket_thread()
{
    if (m_proxy_socket_thread)
    {
        return;
    }

    m_proxy_socket_thread_running = true;

    m_proxy_socket_thread = std::make_unique<std::thread>(&client::proxy_socket_thread_routine, this);
}

void client::stop_proxy_socket_thread()
{
    if (!m_proxy_socket_thread)
    {
        return;
    }

    m_proxy_socket_thread_running = false;

    if (m_proxy_socket_thread->joinable())
    {
        m_proxy_socket_thread->join();
    }
}

void client::get_tunnel_info()
{
    const tunnel_info_request_packet request_packet;
    socket_utils::send(m_proxy_socket, request_packet.serialize());

    reverse_proxy_packet_header header{};
    const buffer header_buffer = socket_utils::recv(m_proxy_socket, sizeof(header));
    std::memcpy(&header, header_buffer.data(), sizeof(header));

    if (header.type != reverse_proxy_packet_type::TUNNEL_INFO_RESPONSE)
    {
        throw tunnel_info_exception("didn't receive tunnel info response");
    }

    const buffer response_buffer = socket_utils::recv(m_proxy_socket, header.length);

    const tunnel_info_response_packet response_packet = tunnel_info_response_packet::deserialize_headerless(
        response_buffer);

    m_tunnel_port = response_packet.get_tunnel_port();
}

void client::proxy_socket_thread_routine()
{
    while (m_proxy_socket_thread_running)
    {
        try
        {
            reverse_proxy_packet_header header{};
            buffer header_buffer = socket_utils::recv(m_proxy_socket, sizeof(header));

            std::memcpy(&header, header_buffer.data(), sizeof(header));

            buffer packet_buffer = socket_utils::recv(m_proxy_socket, header.length);

            handle_packet(header.type, packet_buffer);
        }
        catch (const std::exception& e)
        {
            std::cout << std::format("[ proxy_socket_thread ]: {}", e.what()) << std::endl;
        }
    }
}

void client::handle_packet(const reverse_proxy_packet_type type, const buffer& data)
{
    switch (type)
    {
    case reverse_proxy_packet_type::CLIENT_CONNECTION:
        {
            const client_connection_packet packet = client_connection_packet::deserialize_headerless(data);
            handle_client_connection_packet(packet);
        }
        break;

    case reverse_proxy_packet_type::CLIENT_DISCONNECT:
        {
            const client_disconnect_packet packet = client_disconnect_packet::deserialize_headerless(data);
            handle_client_disconnect_packet(packet);
        }
        break;
    case reverse_proxy_packet_type::ERROR_RESPONSE:
        {
            const error_response_packet packet = error_response_packet::deserialize_headerless(data);
            handle_error_response_packet(packet);
        }
        break;
    }
}

void client::handle_client_connection_packet(const client_connection_packet& packet)
{
    m_connections_manager.create_connection(packet.client_guid(), m_host_port);

    g_task_manager.enqueue(
        std::make_shared<local_socket_recv_task>(m_connections_manager, m_proxy_socket, packet.client_guid()));
}

void client::handle_client_disconnect_packet(const client_disconnect_packet& packet)
{
    m_connections_manager.close_connection(packet.get_client_guid());
}

void client::handle_error_response_packet(const error_response_packet& packet)
{
    throw error_response_exception(packet.get_error_type());
}
