#include "task_manager.h"

#include <iostream>

task_manager::task_manager(const size_t thread_count)
{
    for (size_t i = 0; i < thread_count; i++)
    {
        m_threads.emplace_back(&task_manager::worker_routine, this, i);
    }
}

void task_manager::enqueue(const std::shared_ptr<itask>& task)
{
    std::unique_lock lock(m_tasks_mutex);
    m_tasks.push(task);

    m_cv.notify_one();
}

void task_manager::force_stop()
{
    {
        std::unique_lock lock(m_tasks_mutex);

        m_running = false;
    }

    m_cv.notify_all();

    for (auto& thread : m_threads)
    {
        thread.join();
    }
}

task_manager::~task_manager()
{
    force_stop();
}

void task_manager::worker_routine(uint64_t worker_id)
{
    while (true)
    {
        std::shared_ptr<itask> m_current_task;
        {
            std::unique_lock lock(m_tasks_mutex);

            m_cv.wait(lock, [this]
            {
                return !m_tasks.empty() || !m_running;
            });

            if (!m_running)
            {
                return;
            }

            m_current_task = m_tasks.front();
            m_tasks.pop();
        }

        std::cout << "worker_id " << worker_id << ": ";
        m_current_task->complete();

        if (m_current_task->repeat())
        {
            {
                enqueue(m_current_task);
            }
        }
    }
}
