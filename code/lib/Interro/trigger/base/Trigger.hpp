#pragma once


enum TriggerType { Hardware, Software };
class Trigger
{     
private: 
    TriggerType type;
public:
    Trigger* next;
    Trigger(TriggerType trigger);
    virtual Trigger& configure();
    bool isSoftwareTrigger();
    ~Trigger();
};

