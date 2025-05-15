#pragma once
#include "isocket_task.h"
#include "../tunnel.h"
#include "../tunnel_manager.h"
#include "../packets/ipacket.h"

class host_recv_task : public isocket_task
{
public:
    host_recv_task(socket_manager& socket_manager, tunnel_manager& tunnel_manager, const guid& tunnel_guid);
    ~host_recv_task() override = default;

    void complete() override;
    bool repeat() override;

private:
    void handle_packet(reverse_proxy_packet_type packet_type);

    void handle_tunnel_info() const;

    tunnel_manager& m_tunnel_manager;
    tunnel_guid m_tunnel_guid;
    tunnel& m_tunnel;
};
