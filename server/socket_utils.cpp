#include "socket_utils.h"

#include "exceptions/winsock_exception.h"

void socket_utils::apply_socket_flags(SOCKET socket)
{
    u_long mode = 1;
    ioctlsocket(socket, FIONBIO, &mode);
}

uint16_t socket_utils::get_src_port(const SOCKET socket)
{
    sockaddr_in addr {};
    int addr_len = sizeof(addr);

    if (getsockname(socket, reinterpret_cast<sockaddr*>(&addr), &addr_len) != 0)
    {
        throw winsock_exception("could not get sockets port");
    }

    return ntohs(addr.sin_port);
}
