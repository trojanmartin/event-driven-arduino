#include <Interro.hpp>

TimerPwmConfiguration::TimerPwmConfiguration(volatile uint8_t *TCCRnA,
                                             PwmPin pinA,
                                             PwmPin pinB,
                                             PwmPin pinC) : TCCRnA{TCCRnA},
                                                            pwmPinA(pinA),
                                                            pwmPinB(pinB),
                                                            pwmPinC(pinC)
{
}

PwmPin &TimerPwmConfiguration::getPin(TimerPwmOutput output)
{
    if (output == TimerPwmOutput::OutputA)
    {
        return pwmPinA;
    }

    if (output == TimerPwmOutput::OutputB)
    {
        return pwmPinB;
    }

    return pwmPinC;
}

TimerPwmConfiguration &TimerPwmConfiguration::setUpOutput(TimerPwmOutput output, PwmPinBehavior behavior, uint16_t compareValue)
{
    assert(compareValue <= currentTopValue);

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

    *(pin.OCRnx) = compareValue;
    pin.behavior = behavior;
    return *this;
}