#include <Interro.hpp>

SoftTrigger::SoftTrigger(/* args */) : Trigger(TriggerType::Soft)
{
}

int8_t SoftTrigger::handleCycle()
{
    return UNDEFINED;
}

Trigger &SoftTrigger::configure()
{
    Trigger::configure();
    return *this;
}
