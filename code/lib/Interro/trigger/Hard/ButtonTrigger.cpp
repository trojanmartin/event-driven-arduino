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
    return *this;
}

ButtonTrigger &ButtonTrigger::onClick(const uint8_t event)
{
    onClickEvent = event;
    return *this;
}

uint8_t ButtonTrigger::handleInterrupt(interrupt interrupt)
{
    HardTrigger::handleInterrupt(interrupt);
    if (interrupt != currentInterrupt)
    {
        return 0;
    }

    return debounce_timer.expired(this);
}

ButtonTrigger::~ButtonTrigger()
{
}
