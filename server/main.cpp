#include <iostream>

#include "task_manager.h"
#include "tasks/test_task.h"

int main()
{
    try
    {

    }catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
