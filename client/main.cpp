#include <cstdint>
#include <format>
#include <iostream>

#include "client.h"
#include "config.h"
#include "network_init.h"
#include "task_manager.h"

enum class return_codes : int
{
    SUCCESS = 0,
    NOT_ENOUGH_ARGUMENTS = -1,
    UNHANDLED_EXCEPTION = -2
};

enum class argument_placement
{
    PROXY_ADDRESS = 1,
    HOST_PORT = 2
};

int main(int argc, char** argv)
{
    try
    {
        if (argc < 3)
        {
            std::cout << "Incorrect usage. client.exe <proxy_address> <host_port>" << std::endl;
            system("pause");
            return static_cast<int>(return_codes::NOT_ENOUGH_ARGUMENTS);
        }


        network_init network;

        client client(argv[static_cast<int>(argument_placement::PROXY_ADDRESS)], config::config_port, static_cast<uint16_t>(std::stoi(argv[static_cast<int>(argument_placement::HOST_PORT)])));
        std::cout << std::format("Tunnel port: {}", std::to_string(client.get_tunnel_port())) << std::endl;

        g_task_manager.start(config::thread_count);

        system("pause");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return static_cast<int>(return_codes::UNHANDLED_EXCEPTION);
    }

    return static_cast<int>(return_codes::SUCCESS);
}
