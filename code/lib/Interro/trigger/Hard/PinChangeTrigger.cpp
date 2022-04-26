#include <Interro.hpp>

PinChangeTrigger::PinChangeTrigger(volatile uint8_t *PCMSKn, uint8_t PCIEn, uint8_t minPin, uint8_t maxPin, interrupt interruptId) : PCMSKn{PCMSKn},
                                                                                                                                     PCIEn{PCIEn},
                                                                                                                                     minPin{minPin},
                                                                                                                                     maxPin{maxPin},
                                                                                                                                     interruptId{interruptId}
{
}

PinChangeTrigger &PinChangeTrigger::configure()
{
    Trigger::configure();
    PCICR |= (1 << PCIEn); // PIN CHANGE CONTROL REGISTER
    return *this;
}

PinChangeTrigger &PinChangeTrigger::debounce(const uint32_t millisTime)
{
    debounceTime = millisTime;
    debounceTimer.set(debounceTime);
    return *this;
}

PinChangeTrigger &PinChangeTrigger::onOccurrence(uint8_t event)
{
    onOccurrenceEvent = event;
    return *this;
}

PinChangeTrigger &PinChangeTrigger::enableAnalogPin(uint8_t pin)
{
    return enablePin(arduinoAnalogPinToPCINT(pin));
}

PinChangeTrigger &PinChangeTrigger::enableDigitalPin(uint8_t pin)
{
    return enablePin(arduinoDigitalPinToPCINT(pin));
}

PinChangeTrigger &PinChangeTrigger::enablePin(uint8_t pcint)
{
    assert(minPin <= pcint && pcint <= maxPin);
    *PCMSKn |= (1 << pcint); // enable pin
    return *this;
}

int8_t PinChangeTrigger::handleInterrupt(interrupt interrupt)
{
    if (interrupt != interruptId)
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