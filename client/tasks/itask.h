#pragma once

class itask
{
public:
    virtual ~itask() = default;
    virtual void complete() = 0;
    virtual bool repeat() = 0;
};
