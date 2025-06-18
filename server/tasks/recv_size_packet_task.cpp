#include "recv_size_packet_task.h"

#include "../exceptions/winsock_exception.h"
#include "../exceptions/winsock_nonblock_exception.h"

recv_size_packet_task::recv_size_packet_task(socket_manager& socket_manager, const guid& socket_guid, const size_t recv_size) : m_socket_manager(socket_manager), m_socket_guid(socket_guid), m_recv_size(recv_size)
{
}

void recv_size_packet_task::complete()
{
    try
    {
        const buffer buf = m_socket_manager.recv(m_socket_guid, m_recv_size);

        for (uint8_t c : buf)
        {
            m_buffer.push_back(c);
        }

        m_currently_received += buf.size();
    }catch (const winsock_nonblock_exception& e)
    {
        return;
    }catch (const winsock_exception& e)
    {
        m_winsock_exception = std::make_shared<winsock_exception>(e);
        return;
    }
}

bool recv_size_packet_task::repeat()
{
    return m_currently_received != m_recv_size && m_socket_manager.socket_exists(m_socket_guid) && m_winsock_exception == nullptr;
}

buffer recv_size_packet_task::get_data()
{
    if (m_winsock_exception != nullptr)
    {
        throw *m_winsock_exception;
    }
    return m_buffer;
}
