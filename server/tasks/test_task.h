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
#include <string>

#include "itask.h"

class test_task : public itask
{
public:
    test_task(const std::string& text, bool repeat);

    void complete() override;
    bool repeat() override;

private:
    std::string m_text;
    bool m_repeat;
};
