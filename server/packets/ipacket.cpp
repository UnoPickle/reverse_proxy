#include "ipacket.h"

ipacket::ipacket(const packet_type type) : m_type(type)
{
}

packet_type ipacket::type() const
{
    return m_type;
}
