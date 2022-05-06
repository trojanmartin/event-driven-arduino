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
                           uint8_t onCompareMatchCInterrupt,
                           TimerPwmConfiguration pwm) : TCCRnA{TCCRnA},
                                                        TCCRnB{TCCRnB},
                                                        TCCRnC{TCCRnC},
                                                        OCRnA{OCRnA},
                                                        OCRnB{OCRnB},
                                                        OCRnC{OCRnC},
                                                        TIMSKn{TIMSKn},
                                                        onEverflowInterrupt{onEverflowInterrupt},
                                                        onCompareMatchAInterrupt{onCompareMatchAInterrupt},
                                                        onCompareMatchBInterrupt{onCompareMatchBInterrupt},
                                                        onCompareMatchCInterrupt{onCompareMatchCInterrupt},
                                                        pwmConfiguration(pwm)

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
        *TCCRnB |= (1 << CSn0);  // Set prescaler to 1;
        *TIMSKn |= (1 << TOIEn); // Enable overflow interrupt
        return *this;
    }

    if (timerMode == TimerMode::CTC)
    {
        *TCCRnB |= (1 << WGMn2); // CTC Mode
        return *this;
    }

    // PWM mode is handled in TimerPwmConfiguration
    return *this;
}

TimerTrigger &TimerTrigger::onOverflow(const uint8_t event)
{
    assert(timerMode == TimerMode::Normal);
    onOverflowEvent = event;
    return *this;
}

TimerTrigger &TimerTrigger::setPrescalerValue(Prescalers prescaler)
{
    assert(timerMode != TimerMode::CTC);
    assert(prescaler <= 4);

    setPrescaler(prescaler);
    return *this;
}

TimerTrigger &TimerTrigger::onTime(const uint32_t millis, const uint8_t event)
{
    assert(onCompareMatchAEvent != UNDEFINED);
    return setTimer(millis, event, false);
}

TimerTrigger &TimerTrigger::useInterval(const uint32_t millis, const uint8_t event)
{
    assert(onCompareMatchAEvent == UNDEFINED);
    return setTimer(millis, event, true);
}

TimerTrigger &TimerTrigger::setTimer(const uint32_t millis, const uint8_t event, bool mainInterval)
{
    assert(timerMode == TimerMode::CTC);

    double freq = millis / 1000.0f;
    uint8_t calculatedPrescalerIndex = 0;
    uint16_t compareValue = 0;
    calculateCompareRegisterValue(freq, &calculatedPrescalerIndex, &compareValue);

    uint8_t freeEventSlots = 0;
    if (onCompareMatchAEvent == UNDEFINED)
    {
        setCompareMatchRegister(OCRnA, compareValue, TIMSKn, OCIEnA);
        onCompareMatchAEvent = event;
        ocrnaFrequency = freq;
        freeEventSlots++;
    }
    else if (onCompareMatchBEvent == UNDEFINED)
    {
        setCompareMatchRegister(OCRnB, compareValue, TIMSKn, OCIEnB);
        onCompareMatchBEvent = event;
        ocrnbFrequency = freq;

        assert(ocrnaFrequency >= ocrnbFrequency);
        freeEventSlots++;
    }
    else if (onCompareMatchCEvent == UNDEFINED)
    {
        setCompareMatchRegister(OCRnC, compareValue, TIMSKn, OCIEnC);
        onCompareMatchCEvent = event;
        ocrncFrequency = freq;
        assert(ocrnaFrequency >= ocrncFrequency);
        freeEventSlots++;
    }

    // just check if we handled this properly. If there no free slot user will know that something wrong happend
    assert(freeEventSlots > 0);

    Serial.print("Compare value: ");
    Serial.println(compareValue);

    setPrescaler(calculatedPrescalerIndex);
    return *this;
}

void TimerTrigger::setCompareMatchRegister(volatile uint16_t *occrnx, uint16_t compareValue, volatile uint8_t *timskn, uint8_t ocienx)
{
    *occrnx = compareValue;   // set compare value register
    *timskn |= (1 << ocienx); // enable COMPx interrupts
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

TimerPwmConfiguration &TimerTrigger::getPwmConfigurator()
{
    return pwmConfiguration;
}

TimerPwmConfiguration &TimerTrigger::setPwmMode(PwmMode mode)
{
    if (mode == PwmMode::FastPwm8Bit)
    {
        *TCCRnA |= (1 << WGMn0);
        *TCCRnB |= (1 << WGMn2);
        pwmConfiguration.currentTopValue = 255;
    }
    else if (mode == PwmMode::FastPwm9Bit)
    {
        *TCCRnA |= (1 << WGMn1);
        *TCCRnB |= (1 << WGMn2);
        pwmConfiguration.currentTopValue = 511;
    }
    else if (mode == PwmMode::FastPwm10Bit)
    {
        *TCCRnA |= (1 << WGMn0);
        *TCCRnA |= (1 << WGMn1);
        *TCCRnB |= (1 << WGMn2);
        pwmConfiguration.currentTopValue = 1023;
    }
    else if (mode == PwmMode::PhaseCorrectPwm8bit)
    {
        *TCCRnA |= (1 << WGMn0);
        pwmConfiguration.currentTopValue = 255;
    }
    else if (mode == PwmMode::PhaseCorrectPwm9bit)
    {
        *TCCRnA |= (1 << WGMn1);
        pwmConfiguration.currentTopValue = 511;
    }
    else if (mode == PwmMode::PhaseCorrectPwm10bit)
    {
        *TCCRnA |= (1 << WGMn0);
        *TCCRnA |= (1 << WGMn1);
        pwmConfiguration.currentTopValue = 511;
    }

    pwmConfiguration.mode = mode;
    return pwmConfiguration;
}

// set prescaler
void TimerTrigger::setPrescaler(uint8_t index)
{
    if (prescalerIndex != UNDEFINED)
    {
        // prescaler was already set, we need to try recalculate it
        uint8_t ocraPossiblePrescalerIndexes[5];
        uint16_t ocraPossibleCompareValues[5];
        uint8_t ocrapossibleCount = 0;
        if (*OCRnA != 0)
        {
            getPossiblePrescalers(ocrnaFrequency, ocraPossiblePrescalerIndexes, ocraPossibleCompareValues, &ocrapossibleCount);
        }
        uint8_t ocrbPossiblePrescalerIndexes[5];
        uint16_t ocrbPossibleCompareValues[5];
        uint8_t ocrbpossibleCount = 0;
        if (*OCRnB != 0)
        {
            getPossiblePrescalers(ocrnbFrequency, ocrbPossiblePrescalerIndexes, ocrbPossibleCompareValues, &ocrbpossibleCount);
        }

        uint8_t ocrcPossiblePrescalerIndexes[5];
        uint16_t ocrcPossibleCompareValues[5];
        uint8_t ocrcpossibleCount = 0;
        if (*OCRnC != 0)
        {
            getPossiblePrescalers(ocrncFrequency, ocrcPossiblePrescalerIndexes, ocrcPossibleCompareValues, &ocrcpossibleCount);
        }

        uint8_t result[5];
        uint8_t resultCount = 0;
        if (ocrapossibleCount > 0 && ocrbpossibleCount > 0)
        {
            resultCount = findIntersection(result, ocraPossiblePrescalerIndexes, ocrapossibleCount, ocraPossiblePrescalerIndexes, ocrbpossibleCount);
        }

        uint8_t *finalresult = result;
        uint8_t ocnrcIntersection[5];
        if (*OCRnC != 0)
        {
            resultCount = findIntersection(ocnrcIntersection, result, resultCount, ocrcPossiblePrescalerIndexes, ocrcpossibleCount);
            finalresult = ocnrcIntersection;
        }

        assert(resultCount > 0);

        uint8_t finalPrescalerIndex = finalresult[0];
        setCompareMatchRegister(OCRnA, ocraPossibleCompareValues[getIndexOfValue(ocraPossiblePrescalerIndexes, finalPrescalerIndex)], TIMSKn, OCIEnA);
        setCompareMatchRegister(OCRnB, ocrbPossibleCompareValues[getIndexOfValue(ocrbPossiblePrescalerIndexes, finalPrescalerIndex)], TIMSKn, OCIEnB);

        if (*OCRnC != 0)
        {
            setCompareMatchRegister(OCRnC, ocrcPossibleCompareValues[getIndexOfValue(ocrcPossiblePrescalerIndexes, finalPrescalerIndex)], TIMSKn, OCIEnC);
        }

        index = finalPrescalerIndex;
    }
    Serial.print("Prescaler index: ");
    Serial.println(index + 1);
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
        uint32_t compRegister = (F_CPU / (prescalers[i] / frequency)) - 1;
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
    return (prescalers[prescalerIndex] * (double)(comapareValue + 1)) / F_CPU;
}

void TimerTrigger::getPossiblePrescalers(double frequency, uint8_t prescalerindexes[], uint16_t compareValues[], uint8_t *count)
{
    uint8_t current = 0;
    for (size_t i = 0; i < 5; i++)
    {
        uint32_t compRegister = (F_CPU / (prescalers[i] / frequency)) - 1;
        if (compRegister < maxTick && compRegister > 0)
        {
            prescalerindexes[current] = i;
            compareValues[current] = compRegister;
            current++;
        }
    }

    *count = current;
}

int8_t TimerTrigger::handleInterrupt(interrupt interrupt)
{
    uint8_t event = UNDEFINED;
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

    return event;
}