#pragma once

#include <Interro.hpp>

class ButtonTrigger : SoftTrigger
{
private:
    uint8_t buttonPin;
    uint8_t onClickEvent;
    uint32_t debounceTime = 300;
    TimerMillis debounceTimer;

public:
    virtual int8_t handleCycle();
    ButtonTrigger &configure(const uint8_t pin);
    ButtonTrigger &debounce(const uint32_t millisTime);
    ButtonTrigger &onClick(const uint8_t event);
};
