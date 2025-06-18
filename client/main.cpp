#include <cstdint>
#include <format>
#include <iostream>

#include "client.h"
#include "config.h"
#include "network_init.h"

int main()
{
    try
    {
        network_init network;

        client client("127.0.0.1", config::config_port, 80);
        std::cout << std::format("Tunnel port: {}", std::to_string(client.get_tunnel_port())) << std::endl;

        system("pause");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }

    return 0;
}
