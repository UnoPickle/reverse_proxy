cmake_minimum_required(VERSION 3.31)
project(client)

set(CMAKE_CXX_STANDARD 26)

add_executable(client main.cpp
        exceptions/client_exception.cpp
        exceptions/client_exception.h
        exceptions/winsock_exception.cpp
        exceptions/winsock_exception.h
        network_init.cpp
        network_init.h
        connections_manager.cpp
        connections_manager.h
        exceptions/connection_exception.cpp
        exceptions/connection_exception.h
        exceptions/invalid_connection_exception.cpp
        exceptions/invalid_connection_exception.h
        client.cpp
        client.h
        packets/tunnel_info_request_packet.cpp
        packets/tunnel_info_request_packet.h
        socket_utils.cpp
        socket_utils.h
        exceptions/winsock_nonblock_exception.cpp
        exceptions/winsock_nonblock_exception.h
        exceptions/tunnel_info_exception.cpp
        exceptions/tunnel_info_exception.h
        packets/client_connection_packet.cpp
        packets/client_connection_packet.h
        packets/client_disconnect_packet.cpp
        packets/client_disconnect_packet.h
        packets/communication_packet.cpp
        packets/communication_packet.h
        packets/error_response_packet.cpp
        packets/error_response_packet.h
        packets/ipacket.cpp
        packets/ipacket.h
        config.cpp
        guid.cpp
        exceptions/guid_creation_exception.cpp
        exceptions/guid_creation_exception.h
        packets/tunnel_info_response_packet.cpp)

target_link_libraries(client PRIVATE ws2_32.lib)
