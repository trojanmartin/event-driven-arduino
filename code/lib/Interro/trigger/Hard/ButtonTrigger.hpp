#pragma once

#include <Interro.hpp>

class ButtonTrigger : public HardTrigger
{
private:
    interrupt currentInterrupt;
    uint8_t currentPin;
    uint8_t onClickEvent;
    TimerMillis debounce_timer;
    uint8_t handleInterrupt(interrupt interrupt);

public:
    ButtonTrigger &configure() override;
    ButtonTrigger &onClick(const uint8_t event);
    ButtonTrigger(const uint8_t pin);
    ~ButtonTrigger();
};