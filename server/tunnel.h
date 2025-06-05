#pragma once
#include <memory>
#include <vector>

#include "socket_manager.h"
#include "guid.h"


class tunnel
{
public:
    tunnel(socket_manager& socket_manager, const guid& host, const guid& listener);
    guid accept_client();
    void send_to(const guid& client, const buffer& buffer);
    buffer recv_from(const guid& client, size_t max_len);

    [[nodiscard]] guid host() const;
    [[nodiscard]] guid listener() const;
    [[nodiscard]] const std::vector<guid>& clients() const;

private:
    [[nodiscard]] bool client_in_tunnel(const guid& client);

    guid m_host;
    guid m_listener;

    std::mutex m_clients_mutex;
    std::vector<guid> m_clients;
    socket_manager& m_socket_manager;
};
