#pragma once

#include <Arduino.h>
#include <HardTrigger.hpp>

class PinChangeTrigger : HardTrigger
{
private:
    volatile uint8_t *PCMSKn;
    uint8_t PCIEn;

    uint8_t minPin = 0;
    uint8_t maxPin = 0;

    interrupt interruptId;
    int8_t onOccurrenceEvent = UNDEFINED;
    uint32_t debounceTime = 300;
    TimerMillis debounceTimer;
    int8_t handleInterrupt(interrupt interrupt);

public:
    PinChangeTrigger &configure();
    PinChangeTrigger &debounce(const uint32_t millisTime);
    PinChangeTrigger &onOccurrence(uint8_t event);
    PinChangeTrigger &enablePin(uint8_t pcint);
    PinChangeTrigger &enableDigitalPin(uint8_t pin);
    PinChangeTrigger &enableAnalogPin(uint8_t pin);
    PinChangeTrigger(volatile uint8_t *PCMSKn, uint8_t PCIEn, uint8_t minPin, uint8_t maxPin, interrupt interruptId);
};