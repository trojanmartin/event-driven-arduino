#include <Interro.hpp>

TimerPwmConfiguration::TimerPwmConfiguration(uint8_t timerNumber,
                                             volatile uint8_t *TCCRnA,
                                             PwmPin pinA,
                                             PwmPin pinB,
                                             PwmPin pinC) : timerNumber{timerNumber},
                                                            TCCRnA{TCCRnA},
                                                            pwmPinA(pinA),
                                                            pwmPinB(pinB),
                                                            pwmPinC(pinC)
{
    defaultFastPwmBehavior = PwmPinBehavior::ClearOnCompareMatchFastPwm;
    defaultPhaseCorrectBehavior = PwmPinBehavior::UpClearDownSetOnCompareMatchPhaseCorrectPwm;
}

PwmPin &TimerPwmConfiguration::getPin(TimerPwmOutput output)
{
    if (output == TimerPwmOutput::A)
    {
        return pwmPinA;
    }

    if (output == TimerPwmOutput::B)
    {
        return pwmPinB;
    }

    return pwmPinC;
}

TimerPwmConfiguration &TimerPwmConfiguration::setUpOutput(TimerPwmOutput output, double dutyCycle)
{
    assert(0 <= dutyCycle && dutyCycle <= 1);
    uint16_t compareValue = 0;
    compareValue = dutyCycle * (currentTopValue + 1);

    if (compareValue > currentTopValue)
    {
        compareValue = currentTopValue;
    }

    return setUpOutput(output, mode <= PwmMode::FastPwm10Bit ? defaultFastPwmBehavior : defaultPhaseCorrectBehavior, compareValue);
}

TimerPwmConfiguration &TimerPwmConfiguration::setUpOutput(TimerPwmOutput output, PwmPinBehavior behavior, uint16_t compareValue)
{
    auto pin = getPin(output);

    if (mode <= PwmMode::FastPwm10Bit)
    {
        assert(behavior <= PwmPinBehavior::ClearOnCompareMatchFastPwm);
    }
    else
    {
        assert(behavior >= PwmPinBehavior::UpClearDownSetOnCompareMatchPhaseCorrectPwm);
    }

    uint8_t comnx0 = pin.pinBitx0;
    uint8_t comnx1 = pin.pinBitx1;

    // clear bits.
    *TCCRnA &= ~(1 << comnx0);
    *TCCRnA &= ~(1 << comnx1);

    if (behavior == PwmPinBehavior::ClearOnCompareMatchFastPwm || behavior == PwmPinBehavior::UpClearDownSetOnCompareMatchPhaseCorrectPwm)
    {
        pin.behavior = behavior;
        *TCCRnA |= (1 << comnx1);
    }
    else if (behavior == PwmPinBehavior::SetOnCompareMatchFastPwm || behavior == PwmPinBehavior::UpSetDownSetOnCompareMatchPhaseCorrectPwm)
    {
        *TCCRnA |= (1 << comnx0);
        *TCCRnA |= (1 << comnx1);
    }

    setOutputValue(output, compareValue);
    pinMode(timerPwmOutputToArduinoPin(timerNumber, output), OUTPUT);
    pin.behavior = behavior;
    return *this;
}

TimerPwmConfiguration &TimerPwmConfiguration::setOutputValue(TimerPwmOutput output, uint16_t compareValue)
{
    assert(compareValue <= currentTopValue);
    auto pin = getPin(output);
    *pin.OCRnx = compareValue;
    return *this;
}