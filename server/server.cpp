#include "server.h"

#include "config.h"

server::server() : m_task_manager(config::thread_count)
{
}

server::~server()
{
}
