#include "tunnel_manager.h"

#include "exceptions/tunnel_manager_exception.h"

tunnel_manager::tunnel_manager(socket_manager& socket_manager) : m_socket_manager(socket_manager)
{
}

tunnel_guid tunnel_manager::create_tunnel(const guid& host_guid, const guid& listener_guid)
{
    tunnel_guid new_guid = guid::generate_guid();

    m_tunnels.emplace(new_guid, tunnel(m_socket_manager, host_guid, listener_guid));

    return new_guid;
}

tunnel& tunnel_manager::get_tunnel(const tunnel_guid& guid)
{
    const auto it = m_tunnels.find(guid);

    if (it == m_tunnels.end())
    {
        throw tunnel_manager_exception("could not find tunnel with given tunnel guid");
    }

    return it->second;
}

void tunnel_manager::close_tunnel(const tunnel_guid& tunnel_guid)
{
    const auto it = m_tunnels.find(tunnel_guid);

    if (it == m_tunnels.end())
    {
        throw tunnel_manager_exception("could not find tunnel with given tunnel guid");
    }

    const tunnel tunnel = it->second;

    m_socket_manager.close_socket(tunnel.host());
    m_socket_manager.close_socket(tunnel.listener());

    for (guid client_guid : tunnel.clients())
    {
        m_socket_manager.close_socket(client_guid);
    }

    m_tunnels.erase(it);
}
