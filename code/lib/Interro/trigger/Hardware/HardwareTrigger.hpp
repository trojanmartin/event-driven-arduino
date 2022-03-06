#pragma once

#include <Trigger.hpp>

class HardwareTrigger : public Trigger
{
protected:
    virtual void handleInterrupt(interrupt interrupt) = 0;
    friend class Interro;
public:
    HardwareTrigger();
    virtual Trigger& configure();
    ~HardwareTrigger();
};


