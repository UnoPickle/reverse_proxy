#pragma once
#include "task_manager.h"

class server
{
public:
    server();
    ~server();

private:
    task_manager m_task_manager;
};
