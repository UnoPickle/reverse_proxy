cmake_minimum_required(VERSION 3.31)
project(client)

set(CMAKE_CXX_STANDARD 26)

add_executable(client main.cpp
        exceptions/client_exception.cpp
        exceptions/client_exception.h
        exceptions/winsock_exception.cpp
        exceptions/winsock_exception.h
        network_init.cpp
        network_init.h)

target_link_libraries(client PRIVATE ws2_32.lib)
