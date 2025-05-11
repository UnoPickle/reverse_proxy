

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
