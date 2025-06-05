#pragma once
#include "isocket_task.h"
#include "../tunnel.h"
#include "../tunnel_manager.h"
#include "../packets/ipacket.h"

#include "../socket_utils.h"
#include "../tunnel.h"
#include "../exceptions/winsock_exception.h"
#include "../exceptions/winsock_nonblock_exception.h"
#include "../packets/tunnel_info_response_packet.h"
#include "../packets/communication_packet.h"

class host_recv_task : public isocket_task
{
public:
    host_recv_task(socket_manager& socket_manager, tunnel_manager& tunnel_manager, const guid& tunnel_guid);
    ~host_recv_task() override = default;

    void complete() override;
    bool repeat() override;

private:
    void handle_packet(reverse_proxy_packet_type packet_type, const buffer& data);

    void handle_tunnel_info() const;
    void handle_communication(const communication_packet& data) const;

    tunnel_manager& m_tunnel_manager;
    tunnel_guid m_tunnel_guid;
};
