#pragma once
#include "isocket_task.h"
#include "../tunnel_manager.h"
#include "../packets/ipacket.h"
#include "recv_size_packet_task.h"
#include "../packets/communication_packet.h"
#include "../packets/tunnel_info_response_packet.h"
#include "../socket_utils.h"
#include "../tunnel.h"
#include "../exceptions/winsock_exception.h"
#include "../exceptions/winsock_nonblock_exception.h"


#include "../task_manager.h"
#include "../exceptions/socket_manager_exception.h"
#include "../exceptions/tunnel_exception.h"
#include "../packets/error_response_packet.h"


#include "recv_size_packet_task.h"
#include "../tunnel.h"
#include "../packets/client_disconnect_packet.h"


#include "../packets/communication_packet.h"


class host_recv_task : public isocket_task
{
public:
    host_recv_task(socket_manager& socket_manager, tunnel_manager& tunnel_manager, const tunnel_guid& tunnel_guid);
    ~host_recv_task() override = default;

    void complete() override;
    bool repeat() override;

private:
    void handle_packet(reverse_proxy_packet_type packet_type, const buffer& data);

    void handle_tunnel_info() const;
    void handle_communication(const communication_packet& data) const;
    void handle_client_disconnect(const client_disconnect_packet& const data);

    void handle_unknown_packet();

    bool m_receiving_data = false;
    reverse_proxy_packet_type m_processing_packet_type;

    std::shared_ptr<recv_size_packet_task> m_recv_task = nullptr;
    tunnel_manager& m_tunnel_manager;
    tunnel_guid m_tunnel_guid;
};
