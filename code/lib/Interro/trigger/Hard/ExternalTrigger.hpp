#pragma once

#include <Arduino.h>
#include <HardTrigger.hpp>

enum ExternalTriggerMode
{
    Low,
    Change,
    Failing,
    Rising
};

class ExternalTrigger : HardTrigger
{
private:
    volatile uint8_t *EICRx;
    uint8_t INTn;
    uint8_t ISCn0;
    uint8_t ISCn1;

    interrupt occurrenceInterrupt;
    int8_t onOccurrenceEvent = UNDEFINED;
    uint32_t debounceTime = 300;
    TimerMillis debounceTimer;
    int8_t handleInterrupt(interrupt interrupt);

public:
    ExternalTrigger &configure(ExternalTriggerMode mode);
    ExternalTrigger &debounce(const uint32_t millisTime);
    ExternalTrigger &onOccurrence(uint8_t event);
    ExternalTrigger(volatile uint8_t *EICRx, uint8_t INTn, uint8_t ISCn1, uint8_t ISCn0, interrupt interrupt);
};