#pragma once

#include <Trigger.hpp>

class SoftTrigger : public Trigger
{
private:
    friend class Interro;

public:
    SoftTrigger(/* args */);
    virtual Trigger &configure();
    ~SoftTrigger();
};