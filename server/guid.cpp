// Simple Reverse Proxy - A simple reverse proxy that allows remote
//     clients to connect to a local host
//     Copyright (C) 2025  Hagaib
//
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.

#include "guid.h"

#include <cstring>

#include "exceptions/guid_creation_exception.h"

guid::guid()
{
}

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

bool guid::operator<(const guid& other) const
{
    return std::memcmp(&m_guid, &other.m_guid, sizeof(GUID)) < 0;
}

const GUID* guid::guid_ptr() const
{
    return &m_guid;
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
