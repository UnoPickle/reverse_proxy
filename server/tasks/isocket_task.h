// Simple Reverse Proxy - A simple reverse proxy that allows remote
//     clients to connect to a local host
//     Copyright (C) 2025  Hagaib
//
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.

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
