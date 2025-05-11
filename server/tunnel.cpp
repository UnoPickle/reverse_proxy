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

void tunnel::send_to(const guid& client, const buffer& buffer) const
{
    if (!client_in_tunnel(client))
    {
        throw tunnel_exception("client not found in tunnel");
    }

    m_socket_manager.send(client, buffer);
}

buffer tunnel::recv_from(const guid& client, const size_t max_len) const
{
    if (!client_in_tunnel(client))
    {
        throw tunnel_exception("client not found in tunnel");
    }

    return m_socket_manager.recv(client, max_len);
}

guid tunnel::host() const
{
    return m_host;
}

guid tunnel::listener() const
{
    return m_listener;
}

const std::vector<guid>& tunnel::clients() const
{
    return m_clients;
}

bool tunnel::client_in_tunnel(const guid& client) const
{
    return std::ranges::find(m_clients, client) == m_clients.end();
}
