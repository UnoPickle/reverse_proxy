#pragma once
#include <vector>

#include "guid.h"
#include "socket_manager.h"

class tunnel
{
public:
    tunnel(socket_manager& socket_manager, const guid& host, const guid& listener);
    guid accept_client() const;
    void send_to(const guid& client, const buffer& buffer) const;
    buffer recv_from(const guid& client, const size_t max_len) const;

private:
    bool client_in_tunnel(const guid& client) const;

    guid m_host;
    guid m_listener;

    std::vector<guid> m_clients;
    socket_manager& m_socket_manager;
};
