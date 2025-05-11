#include "client_con_task.h"

#include "../exceptions/winsock_nonblock_exception.h"

client_con_task::client_con_task(socket_manager& socket_manager, tunnel_manager& tunnel_manager,
                                 const tunnel_guid& tunnel_guid) : isocket_task(socket_manager),
                                                                   m_tunnel(tunnel_manager.get_tunnel(tunnel_guid)),
                                                                   m_tunnel_manager(tunnel_manager), m_tunnel_guid(tunnel_guid)
{
}

void client_con_task::complete()
{
    try
    {
        guid new_client_guid = m_socket_manager.accept(m_tunnel.listener());
    }catch (const winsock_nonblock_exception& e)
    {

    }
}

bool client_con_task::repeat()
{
    return m_tunnel_manager.tunnel_exists(m_tunnel_guid);
}
