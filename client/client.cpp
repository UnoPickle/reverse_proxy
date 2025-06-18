#include "client.h"

#include <cstring>
#include <iostream>

#include "socket_utils.h"
#include "exceptions/tunnel_info_exception.h"
#include "packets/ipacket.h"
#include "packets/tunnel_info_request_packet.h"
#include "packets/tunnel_info_response_packet.h"

client::client(const std::string& proxy_address, const uint16_t proxy_port, const uint16_t host_port) : m_host_port(
    host_port)
{
    m_proxy_socket = create_proxy_socket(proxy_address, proxy_port);
    get_tunnel_info();

    std::cout << std::format("Tunnel port: {}", std::to_string(m_tunnel_port)) << std::endl;

    //start_proxy_socket_thread();
}

client::~client()
{
    closesocket(m_proxy_socket);
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
        }
        catch (const std::exception& e)
        {
            std::cout << std::format("[ proxy_socket_thread ]: {}", e.what()) << std::endl;
        }
    }
}
