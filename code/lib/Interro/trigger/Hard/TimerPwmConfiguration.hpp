#pragma once

enum PwmMode
{
    FastPwm,
    PhaseCorrectPwm
};

enum FastPwmModePinBehavior
{
    SetOnCompareMatch,
    ClearOnCompareMatch,
};

enum PhaseCorrectPwmModePinBehavior
{
    UpClearDownSetOnCompareMatch,
    DownClearUpSetOnCompareMatch,
};

enum TimerType
{
    Bit8,
    Bit16
};

class TimerPwmConfiguration
{
private:
    PwmMode mode;
    TimerType timerType;
    uint16_t currentTopValue;
    
    volatile uint16_t *OCRnA;
    volatile uint16_t *OCRnB;
    volatile uint16_t *OCRnC;

    volatile uint8_t *pinRegisterA;
    volatile uint8_t *pinRegisterB;
    volatile uint8_t *pinRegisterC;
public:
    TimerPwmConfiguration &changeCompareValue(uint8_t *pin, double percantage);
    TimerPwmConfiguration &fastPwmPinBehavior(uint8_t *compareMatchPin, FastPwmModePinBehavior behavior, uint16_t compareValue);
    TimerPwmConfiguration &phaseCorrectPwmPinBehavior(uint8_t *compareMatchPin, PhaseCorrectPwmModePinBehavior behavior, uint16_t compareValue);
    TimerPwmConfiguration(/* args */);
};
