#pragma once
#include "itask.h"
#include "../socket_manager.h"

class isocket_task : public itask
{
public:
    isocket_task(socket_manager& socket_manager);
    ~isocket_task() override = default;

    void complete() override = 0;
    bool repeat() override = 0;

protected:
    socket_manager& m_socket_manager;
};
