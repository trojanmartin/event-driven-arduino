#include <Interro.hpp>

ExternalTrigger::ExternalTrigger(volatile uint8_t *EICRx, uint8_t INTn, uint8_t ISCn0, uint8_t ISCn1, interrupt interrupt) : EICRx{EICRx},
                                                                                                                             INTn{INTn},
                                                                                                                             ISCn0{ISCn0},
                                                                                                                             ISCn1{ISCn1},
                                                                                                                             occurrenceInterrupt{interrupt}
{
    *EICRx |= (1 << 1);
    EIMSK |= (1 << INTn); // Enable INTn interrupts
}

ExternalTrigger &ExternalTrigger::configure(ExternalTriggerMode mode)
{
    Trigger::configure();
    debounceTimer.set(debounceTime);
    cli();
    *EICRx |= (((uint8_t)mode) << ISCn0);
    sei();

    return *this;
}

ExternalTrigger &ExternalTrigger::onOccurrence(uint8_t event)
{
    onOccurrenceEvent = event;
    return *this;
}

ExternalTrigger &ExternalTrigger::debounce(const uint32_t millisTime)
{
    debounceTime = millisTime;
    debounceTimer.set(debounceTime);
    return *this;
}

int8_t ExternalTrigger::handleInterrupt(interrupt interrupt)
{
    if (interrupt != occurrenceInterrupt)
    {
        return UNDEFINED;
    }

    if (!debounceTimer.expired(this))
    {
        return UNDEFINED;
    }

    if (onOccurrenceEvent != UNDEFINED)
    {
        trigger_miliss = millis();
        return onOccurrenceEvent;
    }

    return UNDEFINED;
}