#include <iostream>

#include "network_init.h"
#include "task_manager.h"


int main()
{
    try
    {
        network_init network;


    }catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
