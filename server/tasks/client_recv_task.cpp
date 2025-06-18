#include "client_recv_task.h"

#include <iostream>

#include "../exceptions/socket_manager_exception.h"
#include "../exceptions/tunnel_exception.h"
#include "../exceptions/tunnel_manager_exception.h"
#include "../exceptions/winsock_exception.h"
#include "../exceptions/winsock_nonblock_exception.h"
#include "../packets/client_disconnect_packet.h"
#include "../packets/communication_packet.h"

client_recv_task::client_recv_task(socket_manager& socket_manager, tunnel_manager& tunnel_manager,
                                   const tunnel_guid& tunnel_guid,
                                   const guid& client_guid) : isocket_task(socket_manager),
                                                              m_tunnel_manager(tunnel_manager),
                                                              m_tunnel_guid(tunnel_guid), m_client_guid(client_guid)
{
}

void client_recv_task::complete()
{

    try
    {
        const std::shared_ptr<tunnel> tunnel = m_tunnel_manager.get_tunnel(m_tunnel_guid);

        try
        {
            const buffer client_packet = tunnel->recv_from(m_client_guid, CLIENT_RECV_BUFFER_SIZE);
            const communication_packet wrapper_packet(m_client_guid, client_packet);

            m_socket_manager.send(tunnel->host(), wrapper_packet.serialize());
        }catch (const winsock_nonblock_exception& e)
        {
            return;
        }catch (const winsock_exception& e)
        {
            try
            {
                client_disconnect_packet client_disconnect_packet(m_client_guid);
                m_socket_manager.send(tunnel->host(), client_disconnect_packet.serialize());

                tunnel->delete_client(m_client_guid);
            }catch (const std::exception& client_removal_exception)
            {

            }
        }
    }catch (const tunnel_manager_exception& e)
    {

    }catch (const tunnel_exception& e)
    {

    }catch (const socket_manager_exception& e)
    {

    }

}

bool client_recv_task::repeat()
{
    try
    {
        const std::shared_ptr<tunnel> tunnel = m_tunnel_manager.get_tunnel(m_tunnel_guid);
        return m_socket_manager.socket_exists(m_client_guid) && m_socket_manager.socket_exists(tunnel->host());
    }
    catch (const std::exception& e)
    {
        return false;
    }
}
