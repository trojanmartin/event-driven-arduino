#pragma once

#include <Arduino.h>

typedef uint8_t interrupt;

#define INT1_INTERRUPT 0
#define INT2_INTERRUPT 0
#define INT3_INTERRUPT 0
#define INT4_INTERRUPT 1
#define INT5_INTERRUPT 0
#define INT6_INTERRUPT 0
#define INT7_INTERRUPT 0

#define PICINT0_INTERRUPT 0
#define PICINT1_INTERRUPT 0
#define PICINT2_INTERRUPT 0

#define INT1_INTERRUPT_ID 1
#define INT2_INTERRUPT_ID 2
#define INT3_INTERRUPT_ID 3
#define INT4_INTERRUPT_ID 4
#define INT5_INTERRUPT_ID 5
#define INT6_INTERRUPT_ID 6
#define INT7_INTERRUPT_ID 6
#define PICINT0_INTERRUPT_ID 7
#define PICINT1_INTERRUPT_ID 8
#define PICINT2_INTERRUPT_ID 9


class Interro;
class Trigger;
class StateMachine;

extern Interro interro;

class Interro
{
private:
    Trigger* triggerRoot;
    StateMachine* machineRoot;
public:
    void handleInterrupt(interrupt interrupt);
    void onTrigger(uint8_t trigger);
    void run();
    void add(Trigger& trigger);
    void add(StateMachine& machine);
    Interro(/* args */);
    ~Interro();
};

    
#include <dictionary.hpp>
#include <StateConfiguration.hpp>
#include <StateMachine.hpp>


#include <Trigger.hpp>
#include <HardwareTrigger.hpp>

#include <ButtonTrigger.hpp>