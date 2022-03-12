#include <Interro.hpp>

HardTrigger::HardTrigger() : Trigger(TriggerType::Hard)
{
}

void HardTrigger::handleInterrupt(interrupt interrupt)
{
    trigger_miliss = millis();
}