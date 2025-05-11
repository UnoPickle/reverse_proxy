#include "socket_utils.h"

void socket_utils::apply_socket_flags(SOCKET socket)
{
    u_long mode = 1;
    ioctlsocket(socket, FIONBIO, &mode);
}