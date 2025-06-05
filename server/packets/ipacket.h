#pragma once
#include "../buffer.h"

enum class reverse_proxy_packet_type : uint8_t
{
    TUNNEL_INFO_REQUEST = 0,
    TUNNEL_INFO_RESPONSE = 1,
    CLIENT_CONNECTION,
    CLIENT_DISCONNECT,
    //SERVER_DISCONNECT,
    COMMUNICATION,
};

struct reverse_proxy_packet_header
{
    reverse_proxy_packet_type type;
    uint64_t length;
} __attribute__((packed));

class ipacket
{
public:
    explicit ipacket(reverse_proxy_packet_type type);
    virtual ~ipacket() = default;

    [[nodiscard]] reverse_proxy_packet_type type() const;

    [[nodiscard]] virtual size_t packet_size() const = 0;
    [[nodiscard]] virtual buffer serialize() const = 0;


protected:
    const reverse_proxy_packet_type m_type;
};
