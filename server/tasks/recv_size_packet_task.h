#pragma once
#include <memory>

#include "itask.h"
#include "../buffer.h"
#include "../guid.h"
#include "../socket_manager.h"
#include "../exceptions/winsock_exception.h"

class recv_size_packet_task : public itask
{
public:
    recv_size_packet_task(socket_manager& socket_manager, const guid& socket_guid, const size_t recv_size);
    ~recv_size_packet_task() override = default;
    void complete() override;
    bool repeat() override;

    buffer get_data();

private:
    socket_manager& m_socket_manager;
    guid m_socket_guid;
    size_t m_recv_size;

    size_t m_currently_received = 0;
    buffer m_buffer;
    std::shared_ptr<winsock_exception> m_winsock_exception = nullptr;
};
