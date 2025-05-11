#include "socket_manager.h"

#include <memory>
#include <ranges>

#include "exceptions/socket_manager_exception.h"
#include "exceptions/winsock_exception.h"
#include "exceptions/winsock_nonblock_exception.h"


socket_manager::~socket_manager()
{
    for (const guid socket_guid : std::ranges::views::keys(m_sockets))
    {
        close_socket(socket_guid);
    }
}

void socket_manager::send(const guid& socket_guid, const buffer& send_buffer)
{
    const SOCKET socket = get_socket(socket_guid);

    ::send(socket, reinterpret_cast<const char*>(send_buffer.data()), send_buffer.size(), 0);
}

buffer socket_manager::recv(const guid& socket_guid, const size_t max_read_size)
{
    const SOCKET socket = get_socket(socket_guid);

    const std::unique_ptr<uint8_t[]> temp_buffer = std::make_unique<uint8_t[]>(max_read_size);

    ::recv(socket, (char*)temp_buffer.get(), max_read_size, 0);

    return std::vector(temp_buffer.get(), temp_buffer.get() + max_read_size);
}

guid socket_manager::accept(const guid& listener_guid)
{
    const SOCKET socket = get_socket(listener_guid);


    if (const SOCKET new_socket = ::accept(socket, NULL, NULL); new_socket != INVALID_SOCKET)
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

void socket_manager::close_socket(const guid& guid)
{
    SOCKET socket = get_socket(guid);

    ::closesocket(socket);

    m_sockets.erase(guid);
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
