#include <ButtonTrigger.hpp>

ButtonTrigger::ButtonTrigger(const uint8_t pin) : HardTrigger()
{
    currentPin = pin;
}

ButtonTrigger &ButtonTrigger::configure()
{
    Trigger::configure();
    pinMode(currentPin, INPUT);
    EICRB = 0; // reset register value
    EIMSK = 0; // reset register value
    EICRB |= (1 << ISC41);
    EICRB |= (1 << ISC40); // INT4 (Digital pin 2), triggered on RISING edge
    EIMSK |= (1 << INT4);  // Enable only INT4 interrupts
    currentInterrupt = INT4_INTERRUPT_ID;
    debounce_timer.set(500);
    return *this;
}

ButtonTrigger &ButtonTrigger::onClick(const uint8_t event)
{
    onClickEvent = event;
    return *this;
}

void ButtonTrigger::handleInterrupt(interrupt interrupt)
{
    if (interrupt != currentInterrupt)
    {
        return;
    }

    if (debounce_timer.expired(this))
    {
        interro.onEvent(onClickEvent);
        trigger_miliss = millis();
    }
}
