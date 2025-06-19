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

#pragma once
#include <condition_variable>
#include <queue>
#include <vector>

#include "tasks/itask.h"

/*
 * Inspired by GeeksForGeeks' and cppreference's implementations
 */

class task_manager
{
public:
    void start(const size_t thread_count);

    template<typename T, typename ...Args>
    void enqueue(Args&&... args);

    void enqueue(const std::shared_ptr<itask>& task);

    void force_stop();

    ~task_manager();
private:
    void worker_routine(uint64_t worker_id);

    std::queue<std::shared_ptr<itask>> m_tasks;

    std::mutex m_tasks_mutex;
    std::condition_variable m_cv;

    std::vector<std::thread> m_threads;

    bool m_running = true;
};

template <typename T, typename ... Args>
void task_manager::enqueue(Args&&... args)
{
    task_manager::enqueue(std::make_shared<T>(std::forward<Args>(args)...));
}

extern task_manager g_task_manager;
