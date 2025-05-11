#pragma once
#include <map>

#include "guid.h"
#include "tunnel.h"

using tunnel_guid = guid;

class tunnel_manager
{
public:
    explicit tunnel_manager(socket_manager& socket_manager);

    tunnel_guid create_tunnel(const guid& host_guid, const guid& listener_guid);
    tunnel& get_tunnel(const tunnel_guid& guid);

    void close_tunnel(const tunnel_guid& tunnel_guid);

private:
    socket_manager& m_socket_manager;
    std::map<tunnel_guid, tunnel> m_tunnels;
};
