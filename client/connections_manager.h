#pragma once
#include <map>

#include <winsock2.h>
#include "guid.h"

class connections_manager
{
public:
    void add_connection(const guid& guid, SOCKET socket);
    SOCKET get_socket(const guid& guid);
private:
    std::map<guid, SOCKET> m_connections;
};
