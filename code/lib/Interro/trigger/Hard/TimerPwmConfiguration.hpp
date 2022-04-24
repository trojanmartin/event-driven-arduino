#pragma once

enum PwmMode
{
    FastPwm8Bit,
    FastPwm9Bit,
    FastPwm10Bit,
    PhaseCorrectPwm8bit,
    PhaseCorrectPwm9bit,
    PhaseCorrectPwm10bit,
};

enum PwmPinBehavior
{
    NormalBehavior,
    SetOnCompareMatchFastPwm,
    ClearOnCompareMatchFastPwm,

    UpClearDownSetOnCompareMatchPhaseCorrectPwm,
    UpSetDownSetOnCompareMatchPhaseCorrectPwm,
};

enum TimerPwmOutput
{
    A,
    B,
    C,
};

struct PwmPin
{
    uint8_t physicalPin;
    PwmPinBehavior behavior;
    volatile uint16_t *OCRnx;

    uint8_t pinBitx0;
    uint8_t pinBitx1;

    PwmPin(volatile uint16_t *OCRnx, uint8_t pinBitx0, uint8_t pinBitx1) : OCRnx{OCRnx},
                                                                           pinBitx0{pinBitx0},
                                                                           pinBitx1{pinBitx1}
    {
    }
};

class TimerPwmConfiguration
{
private:
    PwmMode mode;
    uint8_t timerNumber;
    uint16_t currentTopValue;

    PwmPinBehavior defaultFastPwmBehavior;
    PwmPinBehavior defaultPhaseCorrectBehavior;

    volatile uint8_t *TCCRnA;
    PwmPin pwmPinA;
    PwmPin pwmPinB;
    PwmPin pwmPinC;
    friend class TimerTrigger;
    PwmPin &getPin(TimerPwmOutput physicalPin);

public:
    TimerPwmConfiguration &setUpOutput(TimerPwmOutput output, PwmPinBehavior behavior, uint16_t compareValue);
    TimerPwmConfiguration &setUpOutput(TimerPwmOutput output, double dutyCycle);
    TimerPwmConfiguration &setOutputValue(TimerPwmOutput output, uint16_t compareValue);
    TimerPwmConfiguration(uint8_t timerNumber,
                          volatile uint8_t *TCCRnA,
                          PwmPin pinA,
                          PwmPin pinB,
                          PwmPin pinC);
};
