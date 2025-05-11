#include "tunnel.h"

#include <algorithm>

#include "exceptions/tunnel_exception.h"


tunnel::tunnel(socket_manager& socket_manager, const guid& host, const guid& listener): m_host(host),
                                                                                        m_listener(listener), m_socket_manager(socket_manager)

{
}

guid tunnel::accept_client() const
{
    return m_socket_manager.accept(m_listener);
}

void tunnel::send_to(const guid& client, const buffer& buffer)
{
    if (std::ranges::find(m_clients, client) == m_clients.end())
    {
        throw tunnel_exception("client not found in tunnel");
    }

    m_socket_manager.send(client, buffer);
}
