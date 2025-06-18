

#include "error_response_exception.h"

error_response_exception::error_response_exception(const error_message_type error_type) : client_exception(error_map.find(error_type)->second)
{
}
