#pragma once
#include "ipacket.h"

struct tunnel_info_packet_struct
{
    reverse_proxy_packet_header header;
    uint16_t tunnel_port;
} __attribute__((packed));

class tunnel_info_packet : public ipacket
{
public:
    explicit tunnel_info_packet(uint16_t tunnel_port);
    ~tunnel_info_packet() override = default;

    [[nodiscard]] size_t packet_size() const override;
    [[nodiscard]] buffer serialize() const override;

private:
    uint16_t m_tunnel_port;
};
