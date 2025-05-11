#include "guid.h"

#include <cstring>

#include "exceptions/guid_creation_exception.h"

guid::guid(const GUID& guid)
{
    memcpy(&m_guid, &guid, sizeof(GUID));
}

guid::guid(const guid& other)
{
    *this = other;
}

guid& guid::operator=(const guid& other)
{
    std::memcpy(&m_guid, &other.m_guid, sizeof(guid));

    return *this;
}

bool guid::operator==(const guid& other) const
{
    return std::memcmp(&m_guid, &other.m_guid, sizeof(GUID)) == 0;
}


guid guid::generate_guid()
{
    GUID guid_buffer;
    if (CoCreateGuid(&guid_buffer) != S_OK)
    {
        throw guid_creation_exception("could not create guid");
    }

    return guid(guid_buffer);
}
