

#pragma once
#include "ipacket.h"

enum class error_message_type : uint8_t
{
    INVALID_PACKET_TYPE = 0,
    INVALID_GUID,
};

struct error_response_packet_struct
{
    reverse_proxy_packet_header header;
    error_message_type error_message_type;
} __attribute__((packed));

class error_response_packet : public ipacket{
public:
    error_response_packet(const error_message_type& type);
    [[nodiscard]] size_t packet_size() const override;
    [[nodiscard]] buffer serialize() const override;
    ~error_response_packet() override = default;

private:
    error_message_type m_error_type;
};
