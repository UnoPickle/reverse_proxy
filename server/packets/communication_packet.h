#pragma once
#include "ipacket.h"
#include "../guid.h"

struct communication_packet_header_struct
{
    reverse_proxy_packet_header header;
    GUID client;
} __attribute__((packed));

class communication_packet : public ipacket
{
public:
    communication_packet(const guid& client, const buffer& packet);

    [[nodiscard]] size_t packet_size() const override;
    [[nodiscard]] buffer serialize() const override;
    static communication_packet deserialize(const buffer& packet);
    static communication_packet deserialize_headerless(const buffer& packet);

    [[nodiscard]] guid client_guid() const;
    [[nodiscard]] buffer payload_packet() const;

private:
    const guid m_client_guid;
    const buffer m_packet;
};
