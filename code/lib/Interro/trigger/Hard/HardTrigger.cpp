#include <Interro.hpp>

HardTrigger::HardTrigger() : Trigger(TriggerType::Hard)
{
}

int8_t HardTrigger::handleInterrupt(interrupt interrupt)
{
    trigger_miliss = millis();
    return UNDEFINED;
}