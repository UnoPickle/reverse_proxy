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
