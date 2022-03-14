#pragma once

#include <Trigger.hpp>

class HardTrigger : public Trigger
{
protected:
    virtual int8_t handleInterrupt(interrupt interrupt);
    friend class Interro;

public:
    HardTrigger();
};
