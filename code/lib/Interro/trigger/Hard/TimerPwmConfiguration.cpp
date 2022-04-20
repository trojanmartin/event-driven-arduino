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

PwmPin &TimerPwmConfiguration::getPin(uint8_t physicalPin)
{
    assert(pwmPinA.physicalPin == physicalPin || pwmPinB.physicalPin == physicalPin || pwmPinC.physicalPin == physicalPin);

    if (pwmPinA.physicalPin == physicalPin)
    {
        return pwmPinA;
    }

    if (pwmPinB.physicalPin == physicalPin)
    {
        return pwmPinB;
    }

    if (pwmPinC.physicalPin == physicalPin)
    {
        return pwmPinC;
    }

    return pwmPinA;
}

TimerPwmConfiguration &TimerPwmConfiguration::setUpPin(uint8_t physicalPin, PwmPinBehavior behavior, uint16_t compareValue)
{
    auto pin = getPin(physicalPin);
    auto reg = pin.OCRnx;
    uint8_t comnx0 = pin.pinBitx0;
    uint8_t comnx1 = pin.pinBitx1;

    // clear bits.
    *TCCRnA &= ~(1 << comnx0);
    *TCCRnA &= ~(1 << comnx1);

    if (behavior == PwmPinBehavior::ClearOnCompareMatch || behavior == PwmPinBehavior::UpClearDownSetOnCompareMatch)
    {
        *TCCRnA |= (1 << comnx1);
    }
    else if (behavior == PwmPinBehavior::SetOnCompareMatch || behavior == PwmPinBehavior::DownClearUpSetOnCompareMatch)
    {
        *TCCRnA |= (1 << comnx0);
        *TCCRnA |= (1 << comnx1);
    }

    *reg = compareValue;
    return *this;
}