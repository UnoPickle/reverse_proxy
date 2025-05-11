#pragma once
#include <winsock2.h>


class network_init
{
public:
    network_init();
    ~network_init();

private:
    WSADATA m_wsa_data;
};
