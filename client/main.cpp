#include <cstdint>
#include <iostream>

#include "network_init.h"


enum class reverse_proxy_packet_type : uint8_t
{
    TUNNEL_INFO_REQUEST = 0
};

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

int main()
{
    try
    {
        network_init network;

        SOCKET test_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
        server_address.sin_port = htons(1212);

        connect(test_socket, reinterpret_cast<sockaddr  *>(&server_address), sizeof(server_address));

        reverse_proxy_packet_header tunnel_info_request = {reverse_proxy_packet_type::TUNNEL_INFO_REQUEST};
        send(test_socket, reinterpret_cast<char*>(&tunnel_info_request), sizeof(tunnel_info_request), 0);

        tunnel_info_response_packet tunnel_info_buffer;
        recv(test_socket, reinterpret_cast<char*>(&tunnel_info_buffer), sizeof(tunnel_info_buffer), 0);

        std::cout << ntohs(tunnel_info_buffer.tunnel_port) << std::endl;

        system("pause");

        closesocket(test_socket);

    }catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }

    return 0;
}
