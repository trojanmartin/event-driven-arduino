#pragma once

#include <Trigger.hpp>

class SoftTrigger : public Trigger
{

protected:
private:
    friend class Interro;

public:
    SoftTrigger();
    virtual int8_t handleCycle();
    virtual Trigger &configure();
};