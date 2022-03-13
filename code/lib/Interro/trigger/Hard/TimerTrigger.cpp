#include <Interro.hpp>

TimerTrigger::TimerTrigger(volatile uint8_t *TCCRnA,
                           volatile uint8_t *TCCRnB,
                           volatile uint8_t *TCCRnC,
                           volatile uint16_t *OCRnA,
                           volatile uint16_t *OCRnB,
                           volatile uint16_t *OCRnC,
                           volatile uint8_t *TIMSKn,
                           uint8_t onEverflowInterrupt,
                           uint8_t onCompareMatchAInterrupt,
                           uint8_t onCompareMatchBInterrupt,
                           uint8_t onCompareMatchCInterrupt) : TCCRnA{TCCRnA},
                                                               TCCRnB{TCCRnB},
                                                               TCCRnC{TCCRnC},
                                                               OCRnA{OCRnA},
                                                               OCRnB{OCRnB},
                                                               OCRnC{OCRnC},
                                                               TIMSKn{TIMSKn},
                                                               onEverflowInterrupt{onEverflowInterrupt},
                                                               onCompareMatchAInterrupt{onCompareMatchAInterrupt},
                                                               onCompareMatchBInterrupt{onCompareMatchBInterrupt},
                                                               onCompareMatchCInterrupt{onCompareMatchCInterrupt}

{
}

TimerTrigger &TimerTrigger::configure(TimerMode mode)
{
    timerMode = mode;
    Trigger::configure();
    *TCCRnA = 0; // reset all timer registers.
    *TCCRnB = 0;
    *TCCRnC = 0;

    if (timerMode == TimerMode::Normal)
    {
        // nothing to do, by resetting timer register we set it to normal mode.
    }
    else
    {
        *TCCRnB |= (1 << WGMn2); // CTC Mode
    }
    return *this;
}

TimerTrigger &TimerTrigger::onOverflow(const uint8_t event)
{
    onOverflowEvent = event;
    return *this;
}

TimerTrigger &TimerTrigger::onEvery(const uint32_t millis, const uint8_t event)
{
    assert(timerMode == TimerMode::CTC);

    uint8_t prescalerIndex = 0;
    uint16_t compareValue = 0;
    calculateCompareRegisterValue(millis / 1000.0f, &prescalerIndex, &compareValue);

    uint8_t freeEventSlots = 0;
    if (onCompareMatchAEvent == UNDEFINED)
    {
        *OCRnA = compareValue;    // set compare value register
        *TIMSKn |= (1 << OCIEnA); // enable COMPA interrupts
        onCompareMatchAEvent = event;
        freeEventSlots++;
    }
    else if (onCompareMatchBEvent == UNDEFINED)
    {
        *OCRnB = compareValue;    // set compare value register
        *TIMSKn |= (1 << OCIEnB); // enable COMPB interrupts
        onCompareMatchBEvent = event;
        freeEventSlots++;
    }
    else if (onCompareMatchCEvent == UNDEFINED)
    {
        *OCRnC = compareValue;    // set compare value register
        *TIMSKn |= (1 << OCIEnC); // enable COMPC interrupts
        onCompareMatchCEvent = event;
        freeEventSlots++;
    }

    // just check if we handled this properly. If there no free slot user will know that something wrong happend
    assert(freeEventSlots > 0);

    setPrescaler(prescalerIndex);

    Serial.print("\n compare value ");
    Serial.print(compareValue);
    Serial.print("\n prescaler value ");
    Serial.print(prescalers[prescalerIndex]);

    return *this;
}

// set prescaler. If the prescaler was already set, aborts program.
void TimerTrigger::setPrescaler(uint8_t index)
{
    if (prescalerIndex != -1)
    {
        // prescaler was already set, we need to try recalculate it
        uint8_t ocraPossiblePrescalerIndexes[5];
        uint16_t ocraPossibleCompareValues[5];
        uint8_t possibleCount = 0;
        getPossiblePrescalers(getFrequency(prescalerIndex, *OCRnA), ocraPossiblePrescalerIndexes, ocraPossibleCompareValues, &possibleCount);
    }

    *TCCRnB |= (index + 1); // set prescaler
    prescalerIndex = index;
}

void TimerTrigger::calculateCompareRegisterValue(double frequency, uint8_t *prescalerIndex, uint16_t *compareValue)
{
    for (size_t i = 0; i < 5; i++)
    {
        uint32_t compRegister = (CLOCK_SPEED / (prescalers[i] / frequency)) - 1;
        if (compRegister < maxTick && compRegister > 0)
        {
            *prescalerIndex = i;
            *compareValue = compRegister;
            return;
        }
    }

    assert(false);
}

double TimerTrigger::getFrequency(uint8_t prescalerIndex, uint16_t comapareValue)
{
    return (prescalers[prescalerIndex] * (comapareValue + 1)) / CLOCK_SPEED;
}

void TimerTrigger::getPossiblePrescalers(double frequency, uint8_t prescalerindexes[], uint16_t compareValues[], uint8_t *count)
{
    uint8_t current = 0;
    for (size_t i = 0; i < 5; i++)
    {
        uint32_t compRegister = (CLOCK_SPEED / (prescalers[i] / frequency)) - 1;
        if (compRegister < maxTick && compRegister > 0)
        {
            prescalerindexes[current] = i;
            compareValues[current] = compRegister;
            current++;
        }
    }
}

void TimerTrigger::handleInterrupt(interrupt interrupt)
{
    uint8_t event;
    if (interrupt == onEverflowInterrupt && onOverflowEvent != UNDEFINED)
    {
        event = onOverflowEvent;
    }
    else if (interrupt == onCompareMatchAInterrupt && onCompareMatchAEvent != UNDEFINED)
    {
        event = onCompareMatchAEvent;
    }
    else if (interrupt == onCompareMatchBInterrupt && onCompareMatchBEvent != UNDEFINED)
    {
        event = onCompareMatchBEvent;
    }
    else if (interrupt == onCompareMatchCInterrupt && onCompareMatchCEvent != UNDEFINED)
    {
        event = onCompareMatchCEvent;
    }
    else
    {
        return;
    }

    interro.onEvent(event);
}