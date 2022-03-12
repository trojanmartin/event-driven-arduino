#include <Timer1Trigger.hpp>

Timer1Trigger::Timer1Trigger(TimerMode mode)
{
    timerMode = mode;
}

Timer1Trigger &Timer1Trigger::configure()
{
    Trigger::configure();
    TCCR1A = 0; // reset all timer registers.
    TCCR1B = 0;
    TCCR1C = 0;

    if (timerMode == TimerMode::Normal)
    {
        // nothing to do, by resetting timer register we set it to normal mode.
    }
    else
    {
        TCCR1B |= (1 << WGM12); // CTC Mode
    }
    return *this;
}

Timer1Trigger &Timer1Trigger::onOverflow(const uint8_t event)
{
    TIMSK1 |= (1 << TOIE1); // enable timer compare interrupt
    TCCR1B |= (1 << CS12);  // prescaler 256

    onOverflowEvent = event;
    return *this;
}

Timer1Trigger &Timer1Trigger::onTimeElapsed(const uint32_t millis, const uint8_t event)
{
    assert(timerMode == TimerMode::CTC);

    if (onCompareMatchAEvent == UNDEFINED)
    {
        uint8_t prescalerIndex = 0;
        uint16_t compareValue = 0;
        calculateCompareRegisterValue(millis / 1000.0f, &prescalerIndex, &compareValue);
        setPrescaler(prescalerIndex);
        OCR1A = compareValue;    // set compare value register
        TIMSK1 |= (1 << OCIE1A); // enable COMPA interrupts
        onCompareMatchAEvent = event;
    }

    return *this;
}

// set prescaler. If the prescaler was already set, aborts program.
void Timer1Trigger::setPrescaler(uint8_t index)
{
    if (prescaler)
    {
        // prescaler cannot be overriden
        assert(prescaler == prescalers[index]);
        return;
    }

    TCCR1B |= (index + 1); // set prescaler
    prescaler = prescalers[index];
}

void Timer1Trigger::calculateCompareRegisterValue(double frequency, uint8_t *prescalerIndex, uint16_t *compareValue)
{
    for (size_t i = 0; i < 5; i++)
    {
        uint32_t compRegister = (CLOCK_SPEED / (prescalers[i] * frequency)) - 1;
        if (compRegister < 65536 && compRegister > 0)
        {
            *prescalerIndex = i;
            *compareValue = compRegister;
            return;
        }
    }

    assert(false);
}

void Timer1Trigger::handleInterrupt(interrupt interrupt)
{
    if (interrupt == Timer1_OVF_INTERRUPT_ID)
    {
        if (onOverflowEvent == UNDEFINED)
        {
            return;
        }

        interro.onEvent(onOverflowEvent);
    }
    else if (interrupt == Timer1_COMPA_INTERRUPT_ID)
    {
        if (onCompareMatchAEvent == UNDEFINED)
        {
            return;
        }

        interro.onEvent(onCompareMatchAEvent);
    }
    else if (interrupt == Timer1_COMPB_INTERRUPT_ID)
    {
        if (onCompareMatchAEvent == UNDEFINED)
        {
            return;
        }

        interro.onEvent(onCompareMatchAEvent);
    }
    else if (interrupt == Timer1_COMPC_INTERRUPT_ID)
    {
        if (onCompareMatchCEvent == UNDEFINED)
        {
            return;
        }

        interro.onEvent(onCompareMatchCEvent);
    }
}