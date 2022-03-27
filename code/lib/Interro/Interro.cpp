#include <Interro.hpp>

Interro interro; // global container

void Interro::add(Trigger &trigger)
{
    trigger.next = triggerRoot;
    triggerRoot = &trigger;
}

void Interro::add(StateMachine &machine)
{
    machine.next = machineRoot;
    machineRoot = &machine;
}

void Interro::run()
{

    Trigger *current;
    current = triggerRoot;
    while (current)
    {
        if (!current->isSoftwareTrigger())
        {
            current = current->next;
            continue;
        }

        int8_t event = static_cast<SoftTrigger *>(current)->handleCycle();
        if (event != UNDEFINED)
        {
            onEvent(event);
        }

        current = current->next;
    }
}

void Interro::handleInterrupt(interrupt interrupt)
{
    Trigger *current;
    current = triggerRoot;
    while (current)
    {
        if (current->isSoftwareTrigger())
        {
            current = current->next;
            continue;
        }

        int8_t event = static_cast<HardTrigger *>(current)->handleInterrupt(interrupt);
        if (event != UNDEFINED)
        {
            onEvent(event);
        }

        current = current->next;
    }
}

void Interro::onEvent(uint8_t event)
{
    StateMachine *current;
    current = machineRoot;
    while (current)
    {
        current->onEvent(event);
        current = current->next;
    }
}

// handle diagnostic informations given by assertion and abort program execution:
void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp)
{
    // transmit diagnostic informations through serial link.
    Serial.println(__func);
    Serial.println(__file);
    Serial.println(__lineno, DEC);
    Serial.println(__sexp);
    Serial.flush();
    // abort program execution.
    abort();
}
