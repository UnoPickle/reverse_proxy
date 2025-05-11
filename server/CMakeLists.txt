cmake_minimum_required(VERSION 3.31)
project(server)

set(CMAKE_CXX_STANDARD 26)

add_executable(server main.cpp
        tasks/itask.cpp
        tasks/itask.h
        tasks/test_task.cpp
        tasks/test_task.h
        task_manager.cpp
        task_manager.h)
