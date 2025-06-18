#pragma once
#include "itask.h"
#include "../guid.h"
#include "../connections_manager.h"

constexpr size_t LOCAL_SOCKET_RECV_BUFFER_SIZE = 1024;

class local_socket_recv_task : public itask
{
public:
    local_socket_recv_task(connections_manager& connections_manager, const SOCKET proxy_socket, const guid& client_guid);
    ~local_socket_recv_task() override = default;

    void complete() override;
    bool repeat() override;

private:
    connections_manager& m_connections_manager;
    SOCKET m_proxy_socket;
    guid m_client_guid;
};
