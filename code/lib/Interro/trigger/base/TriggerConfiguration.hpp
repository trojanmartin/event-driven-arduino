#pragma once

#include <Interro.hpp>

class TriggerConfiguration
{
private:
    uint8_t trigger;
    uint8_t event;
public:
    void fireEvent(const uint8_t event);
    TriggerConfiguration(const uint8_t state);
    ~TriggerConfiguration();
};