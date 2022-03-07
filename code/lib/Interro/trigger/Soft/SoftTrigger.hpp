#pragma once

#include <Trigger.hpp>

class SoftTrigger : public Trigger
{
private:
    void cycle();
    friend class Interro;

public:
    SoftTrigger(/* args */);
    virtual Trigger &configure();
    ~SoftTrigger();
};