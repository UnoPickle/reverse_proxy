#pragma once
#include <map>

#include "tunnel.h"
#include "guid.h"

using tunnel_guid = guid;

class tunnel_manager
{
public:
    explicit tunnel_manager(socket_manager& socket_manager);

    tunnel_guid create_tunnel(const guid& host_guid, const guid& listener_guid);
    std::shared_ptr<tunnel> get_tunnel(const tunnel_guid& guid);

    void close_tunnel(const tunnel_guid& tunnel_guid);

    bool tunnel_exists(const tunnel_guid& tunnel_guid);

private:
    socket_manager& m_socket_manager;

    std::mutex m_tunnels_mutex;
    std::map<tunnel_guid, std::shared_ptr<tunnel>> m_tunnels;
};
