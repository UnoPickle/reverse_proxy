

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

#include "test_task.h"

#include <iostream>
#include <bits/ostream.tcc>

test_task::test_task(const std::string& text, const bool repeat) : m_text(text), m_repeat(repeat)
{

}

void test_task::complete()
{
    std::cout << m_text << std::endl;
}

bool test_task::repeat()
{
    return m_repeat;
}
