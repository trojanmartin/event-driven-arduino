#pragma once

enum TriggerType
{
    Hard,
    Soft
};
class Trigger
{
private:
    TriggerType type;

public:
    Trigger *next;
    uint32_t trigger_miliss;
    Trigger(TriggerType trigger);
    virtual Trigger &configure();
    bool isSoftwareTrigger();
    ~Trigger();
};
