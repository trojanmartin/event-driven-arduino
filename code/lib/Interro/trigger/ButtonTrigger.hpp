#pragma once

#include <Interro.hpp>

class ButtonTrigger{
private:
    uint8_t pin;
    /* data */
public:
    void configure();
    ButtonTrigger(const uint8_t pin);
    ~ButtonTrigger();
};

