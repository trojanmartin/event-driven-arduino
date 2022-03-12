#pragma once

#include <Interro.hpp>

enum TimerMode
{
    Normal,
    CTC
};

class Timer1Trigger : public HardTrigger
{
private:
    const uint16_t prescalers[5]{1, 8, 64, 256, 1024};
    const uint16_t maxTick = 65535;
    uint16_t prescaler = 0;
    TimerMode timerMode;

    int8_t onOverflowEvent = UNDEFINED;
    int8_t onCompareMatchAEvent = UNDEFINED;
    int8_t onCompareMatchBEvent = UNDEFINED;
    int8_t onCompareMatchCEvent = UNDEFINED;
    void handleInterrupt(interrupt interrupt);
    void calculateCompareRegisterValue(double frequency, uint8_t *prescalerIndex, uint16_t *compareValue);
    void setPrescaler(uint8_t index);

public:
    Timer1Trigger &configure() override;
    Timer1Trigger &onOverflow(const uint8_t event);
    Timer1Trigger &onTimeElapsed(const uint32_t miliss, const uint8_t event);
    Timer1Trigger(TimerMode mode);
};