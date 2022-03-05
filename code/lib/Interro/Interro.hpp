#pragma once

#include <Arduino.h>

typedef uint8_t interrupt;

#define INT4_INTERRUPT 1

#ifdef INT4_INTERRUPT
    #define INT4_INTERRUPT_ID 1
#endif

class Interro;

extern Interro interro;

class Interro
{
private:
    /* data */
public:
    void handleInterrupt(interrupt interrupt);
    Interro(/* args */);
    ~Interro();
};

    
#include <dictionary.hpp>
#include <state_configuration.hpp>
#include <state_machine.h>


#include <Trigger.hpp>

#include <ButtonTrigger.hpp>