#pragma once
#include "ipacket.h"
#include "../buffer.h"
#include "../guid.h"

struct client_connection_packet_struct
{
    reverse_proxy_packet_header header;
    GUID client_guid;
} __attribute__((packed));

class client_connection_packet : public ipacket
{
public:
    explicit client_connection_packet(const guid& client_guid);

    [[nodiscard]] guid client_guid() const;

    [[nodiscard]] size_t packet_size() const override;
    [[nodiscard]] buffer serialize() const override;

private:
    const guid m_client_guid;
};
