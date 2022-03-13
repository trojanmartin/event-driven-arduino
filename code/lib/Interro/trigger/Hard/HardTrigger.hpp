#pragma once

#include <Trigger.hpp>

class HardTrigger : public Trigger
{
protected:
    virtual void handleInterrupt(interrupt interrupt);
    friend class Interro;

public:
    HardTrigger();
};
