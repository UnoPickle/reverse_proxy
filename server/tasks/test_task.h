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
