#include <cstdint>
#include <format>
#include <iostream>

#include "network_init.h"


enum class reverse_proxy_packet_type : uint8_t
{
    ERROR_RESPONSE = 0,
    TUNNEL_INFO_REQUEST,
    TUNNEL_INFO_RESPONSE,
    CLIENT_CONNECTION,
    CLIENT_DISCONNECT,
    //SERVER_DISCONNECT,
    COMMUNICATION,
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


        client_connection_packet_struct client_connection_packet {};
        recv(test_socket, reinterpret_cast<char*>(&client_connection_packet), sizeof(client_connection_packet), 0);

        std::cout << "Recieved new client!" << std::endl;


        communication_packet_header_struct communication_packet_header {};
        recv(test_socket, reinterpret_cast<char*>(&communication_packet_header.header), sizeof(reverse_proxy_packet_header), 0);
        recv(test_socket, reinterpret_cast<char*>(&communication_packet_header.client), sizeof(communication_packet_header.client), 0);

        size_t buffer_len = communication_packet_header.header.length - sizeof(communication_packet_header.client);
        char* buffer = new char[buffer_len];
        recv(test_socket, buffer, buffer_len, 0);

        std::cout << std::format("received (len {}): {}", std::to_string(buffer_len), buffer) << std::endl;

        send(test_socket, reinterpret_cast<char*>(&communication_packet_header), sizeof(communication_packet_header), 0);
        send(test_socket, buffer, buffer_len, 0);

        system("pause");

        closesocket(test_socket);

    }catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }

    return 0;
}
