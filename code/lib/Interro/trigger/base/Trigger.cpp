#include <Interro.hpp>

Trigger::Trigger(TriggerType trigger)
{
    type = trigger;
}

Trigger &Trigger::configure()
{
    interro.add(*this);
    return *this;
}

bool Trigger::isSoftwareTrigger()
{
    return type == TriggerType::Soft;
}
