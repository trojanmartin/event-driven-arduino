#pragma once

#include <Interro.hpp>

class ButtonTrigger : public HardwareTrigger {
private:
    interrupt currentInterrupt;
    void handleInterrupt(interrupt interrupt); 
    uint8_t currentPin;
    uint8_t onClickTrigger;
public:
    ButtonTrigger& configure() override;
    ButtonTrigger& onClick(const uint8_t trigger);
    ButtonTrigger(const uint8_t pin);
    ~ButtonTrigger();
};