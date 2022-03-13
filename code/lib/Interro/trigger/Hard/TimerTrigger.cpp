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
        setCompareMatchRegister(OCRnA, compareValue, TIMSKn, OCIEnA);
        onCompareMatchAEvent = event;
        freeEventSlots++;
    }
    else if (onCompareMatchBEvent == UNDEFINED)
    {
        setCompareMatchRegister(OCRnB, compareValue, TIMSKn, OCIEnB);
        onCompareMatchBEvent = event;
        freeEventSlots++;
    }
    else if (onCompareMatchCEvent == UNDEFINED)
    {
        setCompareMatchRegister(OCRnC, compareValue, TIMSKn, OCIEnC);
        onCompareMatchCEvent = event;
        freeEventSlots++;
    }

    // just check if we handled this properly. If there no free slot user will know that something wrong happend
    assert(freeEventSlots > 0);

    setPrescaler(prescalerIndex);
    return *this;
}

void TimerTrigger::setCompareMatchRegister(volatile uint16_t *occrnx, uint16_t compareValue, volatile uint8_t *timskn, uint8_t ocienx)
{
    Serial.print("\n setting compare register to ");
    Serial.print(compareValue);

    *occrnx = compareValue;   // set compare value register
    *timskn |= (1 << ocienx); // enable COMPC interrupts
}

uint8_t getIndexOfValue(uint8_t *array, uint8_t value)
{
    for (size_t i = 0; i < 5; i++)
    {
        if (array[i] == value)
        {
            return i;
        }
    }

    return 0;
}

// set prescaler
void TimerTrigger::setPrescaler(uint8_t index)
{
    if (prescalerIndex != -1)
    {
        // prescaler was already set, we need to try recalculate it
        uint8_t ocraPossiblePrescalerIndexes[5];
        uint16_t ocraPossibleCompareValues[5];
        uint8_t ocrapossibleCount = 0;
        if (*OCRnA != 0)
        {
            getPossiblePrescalers(getFrequency(prescalerIndex, *OCRnA), ocraPossiblePrescalerIndexes, ocraPossibleCompareValues, &ocrapossibleCount);
        }

        uint8_t ocrbPossiblePrescalerIndexes[5];
        uint16_t ocrbPossibleCompareValues[5];
        uint8_t ocrbpossibleCount = 0;
        if (*OCRnB != 0)
        {
            getPossiblePrescalers(getFrequency(prescalerIndex, *OCRnB), ocrbPossiblePrescalerIndexes, ocrbPossibleCompareValues, &ocrbpossibleCount);
        }

        uint8_t ocrcPossiblePrescalerIndexes[5];
        uint16_t ocrcPossibleCompareValues[5];
        uint8_t ocrcpossibleCount = 0;
        if (*OCRnC != 0)
        {
            getPossiblePrescalers(getFrequency(prescalerIndex, *OCRnC), ocrcPossiblePrescalerIndexes, ocrcPossibleCompareValues, &ocrcpossibleCount);
        }

        uint8_t result[5];
        uint8_t resultCount = 0;
        if (ocrapossibleCount > 0 && ocrbpossibleCount > 0)
        {
            resultCount = findIntersection(result, ocraPossiblePrescalerIndexes, ocrapossibleCount, ocraPossiblePrescalerIndexes, ocrbpossibleCount);
        }

        if (*OCRnC != 0)
        {
            uint8_t finalresult[5];
            resultCount = findIntersection(finalresult, result, resultCount, ocrcPossiblePrescalerIndexes, ocrcpossibleCount);
        }

        assert(resultCount > 0);

        for (size_t i = 0; i < resultCount; i++)
        {
        }

        uint8_t finalPrescalerIndex = result[0];
        setCompareMatchRegister(OCRnA, ocraPossibleCompareValues[getIndexOfValue(ocraPossiblePrescalerIndexes, finalPrescalerIndex)], TIMSKn, OCIEnA);
        setCompareMatchRegister(OCRnB, ocrbPossibleCompareValues[getIndexOfValue(ocrbPossiblePrescalerIndexes, finalPrescalerIndex)], TIMSKn, OCIEnB);

        Serial.print("\n ocrA");
        Serial.print(ocraPossibleCompareValues[getIndexOfValue(ocraPossiblePrescalerIndexes, finalPrescalerIndex)]);
        index = finalPrescalerIndex;
    }
    *TCCRnB |= (index + 1); // set prescaler
    prescalerIndex = index;
}

uint8_t TimerTrigger::findIntersection(uint8_t result[], uint8_t first[], size_t firstCount, uint8_t second[], size_t secondCount)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < firstCount; i++)
    {
        for (uint8_t j = 0; j < secondCount; j++)
        {
            if (first[i] == second[j])
            {
                result[count] = first[i];
                count++;
            }
        }
    }

    return count;
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
    return (prescalers[prescalerIndex] * (double)(comapareValue + 1)) / CLOCK_SPEED;
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

    *count = current;
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