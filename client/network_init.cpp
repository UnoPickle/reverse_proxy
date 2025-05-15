#include "network_init.h"
#include "exceptions/winsock_exception.h"

network_init::network_init()
{
    if (WSAStartup(MAKEWORD(2, 2), &m_wsa_data) != NO_ERROR)
    {
        throw winsock_exception("could not initialize WSA");
    }
}

network_init::~network_init()
{
    WSACleanup();
}
