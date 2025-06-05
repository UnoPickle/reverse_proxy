#include "host_client_con_task.h"

#include <iostream>

#include "../exceptions/tunnel_manager_exception.h"
#include "../exceptions/winsock_nonblock_exception.h"

host_client_con_task::host_client_con_task(socket_manager& socket_manager, tunnel_manager& tunnel_manager,
                                 const tunnel_guid& tunnel_guid) : isocket_task(socket_manager),
                                                                   m_tunnel_manager(tunnel_manager), m_tunnel_guid(tunnel_guid)
{
}

void host_client_con_task::complete()
{
    try
    {
        const std::shared_ptr<tunnel> tunnel = m_tunnel_manager.get_tunnel(m_tunnel_guid);

        guid new_client_guid = tunnel->accept_client();
    }catch (const winsock_nonblock_exception& e)
    {

    }catch (const tunnel_manager_exception& e)
    {

    }
}

bool host_client_con_task::repeat()
{
    return m_tunnel_manager.tunnel_exists(m_tunnel_guid);
}
