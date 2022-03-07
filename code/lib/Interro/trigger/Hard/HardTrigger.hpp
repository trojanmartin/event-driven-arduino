#pragma once

#include <Trigger.hpp>

class HardTrigger : public Trigger
{
protected:
    virtual uint8_t handleInterrupt(interrupt interrupt);
    friend class Interro;

public:
    HardTrigger();
    virtual Trigger &configure();
};
