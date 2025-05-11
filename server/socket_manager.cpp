#include "socket_manager.h"

#include "exceptions/socket_manager_exception.h"

void socket_manager::send(const guid& socket_guid, const buffer& send_buffer)
{
    SOCKET socket = get_socket(socket_guid);

    ::send(socket, reinterpret_cast<const char*>(send_buffer.data()), send_buffer.size(), 0);
}

buffer socket_manager::recv(const guid& socket_guid, const size_t max_read_size)
{
    SOCKET socket = get_socket(socket_guid);

    buffer recv_buffer(max_read_size);
    ::recv(socket, (char*)recv_buffer.data(), max_read_size, 0);

    return recv_buffer;
}

SOCKET socket_manager::get_socket(const guid& socket_guid)
{
    const auto sock_it = m_sockets.find(socket_guid);

    if (sock_it == m_sockets.end())
    {
        throw socket_manager_exception("not socket found with given guid");
    }

    return sock_it->second;
}
