#include "ipacket.h"

ipacket::ipacket(const reverse_proxy_packet_type type) : m_type(type)
{
}

reverse_proxy_packet_type ipacket::type() const
{
    return m_type;
}
