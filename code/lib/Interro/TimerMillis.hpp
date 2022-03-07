#pragma once

class TimerMillis
{
public:
    uint32_t value;
    void set(uint32_t v);
    int expired(Trigger *trigger);
};