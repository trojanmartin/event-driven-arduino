#pragma once

#include <Trigger.hpp>

class SoftTrigger : public Trigger
{

protected:
    

private:
    friend class Interro;

public:
    SoftTrigger();
    void cycle();
    virtual Trigger &configure();
};