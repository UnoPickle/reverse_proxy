#include <cstdint>
#include <format>
#include <iostream>

#include "client.h"
#include "config.h"
#include "network_init.h"


struct reverse_proxy_packet_header
{
    reverse_proxy_packet_type type;
    uint64_t length;
} __attribute__((packed));

struct tunnel_info_response_packet
{
    reverse_proxy_packet_header header { reverse_proxy_packet_type::TUNNEL_INFO_REQUEST};
    uint16_t tunnel_port;
} __attribute__((packed));

struct communication_packet_header_struct
{
    reverse_proxy_packet_header header;
    GUID client;
} __attribute__((packed));

struct client_connection_packet_struct
{
    reverse_proxy_packet_header header;
    GUID client_guid;
} __attribute__((packed));

int main()
{
    try
    {
        network_init network;

        client client("127.0.0.1", config::config_port ,80);

        system("pause");


    }catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }

    return 0;
}
