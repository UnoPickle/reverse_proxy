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

#include <iostream>

#include "network_init.h"
#include "server.h"
#include "task_manager.h"


int main()
{
    try
    {
        network_init network;
        server server;

        system("pause");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
