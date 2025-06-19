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

#pragma once
#include <combaseapi.h>

class guid
{
public:
    guid();
    explicit guid(const GUID& guid);
    guid(const guid& other);
    guid& operator=(const guid& other);
    bool operator==(const guid& other) const;
    bool operator<(const guid& other) const;
    const GUID* guid_ptr() const;


    static guid generate_guid();
private:
    GUID m_guid = {};
};
