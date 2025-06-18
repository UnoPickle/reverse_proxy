#include "socket_utils.h"

#include <memory>

#include "exceptions/winsock_exception.h"
#include "exceptions/winsock_nonblock_exception.h"

int socket_utils::send(const SOCKET socket, const buffer& buffer)
{
    return ::send(socket, reinterpret_cast<const char*>(buffer.data()), buffer.size(), 0);
}

buffer socket_utils::recv(SOCKET socket, const size_t max_read_size)
{
    const std::unique_ptr<uint8_t[]> temp_buffer = std::make_unique<uint8_t[]>(max_read_size);

    if (int read_size = ::recv(socket, reinterpret_cast<char*>(temp_buffer.get()), max_read_size, 0); read_size != SOCKET_ERROR)
    {
        if (read_size == 0)
        {
            throw winsock_exception("couldn't read from socket");
        }

        return buffer(temp_buffer.get(), temp_buffer.get() + read_size);
    }

    int last_error = WSAGetLastError();

    if (last_error == WSAEWOULDBLOCK)
    {
        throw winsock_nonblock_exception("no data queued");
    }
    else
    {
        throw winsock_exception("couldn't read from socket");
    }
}
