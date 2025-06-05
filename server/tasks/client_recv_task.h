#pragma once
#include "isocket_task.h"
#include "../tunnel_manager.h"

constexpr size_t CLIENT_RECV_BUFFER_SIZE = 1024;

class client_recv_task : public isocket_task
{
public:
    client_recv_task(socket_manager& socket_manager, tunnel_manager& tunnel_manager, const tunnel_guid& tunnel_guid, const guid& client_guid);
    ~client_recv_task() override = default;
    void complete() override;
    bool repeat() override;

private:
    tunnel_manager& m_tunnel_manager;
    tunnel_guid m_tunnel_guid;
    guid m_client_guid;
};
