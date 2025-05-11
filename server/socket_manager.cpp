#include "socket_manager.h"

#include <ranges>

#include "exceptions/socket_manager_exception.h"
#include "exceptions/winsock_exception.h"
#include "exceptions/winsock_nonblock_exception.h"


socket_manager::~socket_manager()
{
    for (const SOCKET socket_entry : std::ranges::views::values(m_sockets))
    {
        ::closesocket(socket_entry);
    }
}

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

guid socket_manager::accept(const guid& listener_guid)
{
    SOCKET socket = get_socket(listener_guid);

    SOCKET new_socket = ::accept(socket, NULL, NULL);


    if (new_socket != INVALID_SOCKET)
    {
        return add_socket(new_socket);
    }

    int last_error = WSAGetLastError();

    if (last_error == WSAEWOULDBLOCK)
    {
        throw winsock_nonblock_exception("no clients queued");
    }else
    {
        throw winsock_exception("couldn't accept socket");
    }

}

guid socket_manager::add_socket(const SOCKET socket)
{
    guid new_guid = guid::generate_guid();
     m_sockets.emplace(new_guid, socket);

    return new_guid;
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
