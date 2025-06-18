#pragma once
#include "ipacket.h"

struct tunnel_info_request_packet_struct
{
    reverse_proxy_packet_header header;
} __attribute__((packed));

class tunnel_info_request_packet : public ipacket
{
public:
    tunnel_info_request_packet();
    ~tunnel_info_request_packet() override = default;
    [[nodiscard]] size_t packet_size() const override;
    [[nodiscard]] buffer serialize() const override;
};
