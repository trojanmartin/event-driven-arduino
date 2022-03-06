#include <Interro.hpp>

Interro interro; //global container

Interro::Interro()
{
}

Interro::~Interro()
{
}

void Interro::add(Trigger& trigger)
{
    trigger.next = triggerRoot;
    triggerRoot = &trigger;
}

void Interro::add(StateMachine& machine)
{
    machine.next = machineRoot;
    machineRoot = &machine;
}

void Interro::run()
{
  /*  Trigger* current;
    current = root;
    while(current)
    {
        if(current->isSoftwareTrigger())
        {
            current->cycle();
        }
        current = current->next;
    }
    */
}

void Interro::handleInterrupt(interrupt interrupt)
{
    Trigger* current;
    current = triggerRoot;
    while(current)
    {
        if(current->isSoftwareTrigger())
        {
            current = current->next;
            continue;
        }
                        
        static_cast<HardwareTrigger*>(current)->handleInterrupt(interrupt);
        current = current->next;        
    }
}

void Interro::onEvent(uint8_t event)
{    
    StateMachine* current;
    current = machineRoot;
    while(current)
    {
        current->onEvent(event);
        current = current->next;
    }
}