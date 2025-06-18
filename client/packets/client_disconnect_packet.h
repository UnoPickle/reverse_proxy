#pragma once
#include "ipacket.h"
#include "../guid.h"

struct client_disconnect_packet_struct
{
    reverse_proxy_packet_header header;
    GUID client_guid;
};

class client_disconnect_packet : public ipacket
{
public:
    client_disconnect_packet(const guid& client_guid);
    ~client_disconnect_packet() override = default;

    guid get_client_guid() const;

    [[nodiscard]] size_t packet_size() const override;
    [[nodiscard]] buffer serialize() const override;
    client_disconnect_packet deserialize_headerless(const buffer& buffer);

private:
    guid m_client_guid;
};
