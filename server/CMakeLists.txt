cmake_minimum_required(VERSION 3.31)
project(server)

set(CMAKE_CXX_STANDARD 26)

add_executable(server main.cpp
        tasks/itask.cpp
        tasks/itask.h
        tasks/test_task.cpp
        tasks/test_task.h
        task_manager.cpp
        task_manager.h
        server.cpp
        server.h
        exceptions/server_exception.cpp
        exceptions/server_exception.h
        socket_manager.cpp
        socket_manager.h
        guid.cpp
        guid.h
        exceptions/guid_creation_exception.cpp
        exceptions/guid_creation_exception.h
        network_init.cpp
        network_init.h
        exceptions/winsock_exception.cpp
        exceptions/winsock_exception.h
        buffer.h
        exceptions/socket_manager_exception.cpp
        exceptions/socket_manager_exception.h
        exceptions/winsock_nonblock_exception.cpp
        exceptions/winsock_nonblock_exception.h
        socket_utils.cpp
        socket_utils.h
        config.cpp
        config.h
        tunnel.cpp
        tunnel.h
        exceptions/tunnel_exception.cpp
        exceptions/tunnel_exception.h
        tunnel_manager.cpp
        tunnel_manager.h
        exceptions/tunnel_manager_exception.cpp
        exceptions/tunnel_manager_exception.h
        tasks/isocket_task.cpp
        tasks/isocket_task.h
        packets/ipacket.cpp
        packets/ipacket.h
        packets/client_connection_packet.cpp
        packets/client_connection_packet.h
        tasks/host_client_con_task.cpp
        tasks/host_client_con_task.h
        tasks/host_recv_task.cpp
        tasks/host_recv_task.h
        packets/communication_packet.cpp
        packets/communication_packet.h
        tasks/client_recv_task.cpp
        tasks/client_recv_task.h
        packets/error_response_packet.cpp
        packets/error_response_packet.h
        packets/client_disconnect_packet.cpp
        packets/client_disconnect_packet.h
        tasks/recv_size_packet_task.cpp
        tasks/recv_size_packet_task.h
        packets/tunnel_info_response_packet.cpp
)

target_link_libraries(server PRIVATE ws2_32.lib)
