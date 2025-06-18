#pragma once
#include <map>

#include "client_exception.h"

#include "../packets/error_response_packet.h"

const std::map<error_message_type, std::string> error_map = { {error_message_type::INVALID_GUID, "Invalid guid"} };

class error_response_exception : public client_exception
{
public:
    explicit error_response_exception(const error_message_type error_type);
    ~error_response_exception() noexcept override = default;
};
