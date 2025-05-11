#pragma once
#include "socket_manager.h"
#include "task_manager.h"

class server
{
public:
    server();
    ~server();

private:
    task_manager m_task_manager;
    socket_manager g_socket_manager;
};
