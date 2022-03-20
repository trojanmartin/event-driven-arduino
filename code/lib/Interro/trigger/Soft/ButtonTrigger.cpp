#include <ButtonTrigger.hpp>

ButtonTrigger &ButtonTrigger::configure(const uint8_t pin)
{
    SoftTrigger::configure();
    buttonPin = pin;
    pinMode(buttonPin, INPUT);
    debounceTimer.set(debounceTime);
    return *this;
}

ButtonTrigger &ButtonTrigger::onClick(const uint8_t event)
{
    onClickEvent = event;
    return *this;
}

ButtonTrigger &ButtonTrigger::debounce(const uint32_t millisTime)
{
    debounceTime = millisTime;
    debounceTimer.set(debounceTime);
    return *this;
}

int8_t ButtonTrigger::handleCycle()
{
    if (!debounceTimer.expired(this))
    {
        return UNDEFINED;
    }

    if (digitalRead(buttonPin) == HIGH)
    {
        trigger_miliss = millis();
        return onClickEvent;
    }

    return UNDEFINED;
}
