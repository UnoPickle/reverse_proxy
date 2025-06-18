#include "connections_manager.h"

#include <format>
#include <iostream>

#include "socket_utils.h"
#include "exceptions/invalid_connection_exception.h"
#include "exceptions/winsock_exception.h"


SOCKET connections_manager::create_connection(const guid& client_guid, const uint16_t host_port)
{
    SOCKET local_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (local_socket == INVALID_SOCKET)
    {
        throw winsock_exception("couldn't create local socket");
    }

    socket_utils::apply_socket_flags(local_socket);

    sockaddr_in local_address;
    local_address.sin_family = AF_INET;
    local_address.sin_port = htons(host_port);
    local_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(local_socket, (sockaddr*)&local_address, sizeof(local_address)) == SOCKET_ERROR)
    {
        if (int error = WSAGetLastError(); error == WSAEWOULDBLOCK || error == WSAEINPROGRESS)
        {
            fd_set writefds;
            FD_ZERO(&writefds);
            FD_SET(local_socket, &writefds);

            TIMEVAL timeout;
            timeout.tv_sec = 5; // Wait up to 5 seconds
            timeout.tv_usec = 0;

            int sel_result = select(0, NULL, &writefds, NULL, &timeout);
            if (sel_result > 0 && FD_ISSET(local_socket, &writefds))
            {
                int so_error = 0;
                int optlen = sizeof(so_error);
                getsockopt(local_socket, SOL_SOCKET, SO_ERROR, (char*)&so_error, &optlen);
                if (so_error != 0)
                {
                    closesocket(local_socket);
                    throw winsock_exception(std::format("couldn't connect local socket to port {}", host_port));
                }
                // Connected successfully!
            }
            else
            {
                closesocket(local_socket);
                throw winsock_exception(std::format("timeout or error connecting to port {}", host_port));
            }
        }
        else
        {
            closesocket(local_socket);
            throw winsock_exception(std::format("couldn't connect local socket to port {}", host_port));
        }
    }

    m_connections.insert(std::make_pair(client_guid, local_socket));
    return local_socket;
}

SOCKET connections_manager::get_socket(const guid& guid)
{
    const auto it = m_connections.find(guid);

    if (it == m_connections.end())
    {
        throw invalid_connection_exception("no socket found");
    }

    return it->second;
}

void connections_manager::close_connection(const guid& guid)
{
    const SOCKET local_socket = get_socket(guid);
    if (closesocket(local_socket) == SOCKET_ERROR)
    {
        throw winsock_exception("couldn't close local socket");
    }

    m_connections.erase(guid);
}

bool connections_manager::connection_exists(const guid& guid) const
{
    return m_connections.contains(guid);
}

int connections_manager::send_to(const guid& client_guid, const buffer& buffer)
{
    const SOCKET socket = get_socket(client_guid);

    return socket_utils::send(socket, buffer);
}

buffer connections_manager::recv_from(const guid& client_guid, const size_t max_read_size)
{
    const SOCKET socket = get_socket(client_guid);

    return socket_utils::recv(socket, max_read_size);
}
