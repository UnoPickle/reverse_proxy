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

    static guid generate_guid();
private:
    GUID m_guid = {};
};
