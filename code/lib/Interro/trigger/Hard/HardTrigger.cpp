#include <Interro.hpp>

HardTrigger::HardTrigger() : Trigger(TriggerType::Hard)
{
}

uint8_t HardTrigger::handleInterrupt(interrupt interrupt)
{
    trigger_miliss = millis();
    return 0;
}