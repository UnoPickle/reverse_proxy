#include "connections_manager.h"

#include "exceptions/invalid_connection_exception.h"

void connections_manager::add_connection(const guid& guid, SOCKET socket)
{
    m_connections.insert(std::make_pair(guid, socket));
}

SOCKET connections_manager::get_socket(const guid& guid)
{
    const auto it = m_connections.find(guid);

    if (it == m_connections.end())
    {
        throw invalid_connection_exception("no socket found");
    }

    return it->second;
}
