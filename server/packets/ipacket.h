#pragma once
#include "packet_type.h"
#include "../buffer.h"

struct  reverse_proxy_packet_header
{
    uint8_t type;
} __attribute__((packed));

class ipacket
{
public:
    explicit ipacket(packet_type type);
    virtual ~ipacket() = default;

    [[nodiscard]] packet_type type() const;

     [[nodiscard]] virtual size_t packet_size() const = 0;
    [[nodiscard]] virtual buffer serialize() const = 0;
protected:
    const packet_type m_type;
};
