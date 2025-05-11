#pragma once
#include "isocket_task.h"
#include "../tunnel_manager.h"

class client_con_task : public isocket_task
{
public:
    client_con_task(socket_manager& socket_manager, tunnel_manager& tunnel_manager, const tunnel_guid& tunnel_guid);
    ~client_con_task() override = default;

    void complete() override;
    bool repeat() override;

private:
    tunnel& m_tunnel;
    tunnel_manager& m_tunnel_manager;
    tunnel_guid m_tunnel_guid;
};

