#pragma once

enum PwmMode
{
    FastPwm8Bit,
    PhaseCorrectPwm
};

enum PwmPinBehavior
{
    NormalBehavior,
    SetOnCompareMatch,
    ClearOnCompareMatch,

    UpClearDownSetOnCompareMatch,
    DownClearUpSetOnCompareMatch,
};

enum TimerType
{
    Bit8,
    Bit16
};

struct PwmPin
{
    uint8_t physicalPin;
    PwmPinBehavior behavior;
    volatile uint16_t *OCRnx;

    uint8_t pinBitx0;
    uint8_t pinBitx1;

    PwmPin(uint8_t physicalPin, volatile uint16_t *OCRnx, uint8_t pinBitx0, uint8_t pinBitx1) : physicalPin{physicalPin},
                                                                                                OCRnx{OCRnx},
                                                                                                pinBitx0{pinBitx0},
                                                                                                pinBitx1{pinBitx1}
    {
    }
};

class TimerPwmConfiguration
{
private:
    PwmMode mode;
    TimerType timerType;
    uint16_t currentTopValue;

    volatile uint8_t *TCCRnA;
    PwmPin pwmPinA;
    PwmPin pwmPinB;
    PwmPin pwmPinC;
    friend class TimerTrigger;
    PwmPin &getPin(uint8_t physicalPin);

public:
    TimerPwmConfiguration &setUpPin(uint8_t physicalPin, PwmPinBehavior behavior, uint16_t compareValue);
    TimerPwmConfiguration(volatile uint8_t *TCCRnA,
                          PwmPin pinA,
                          PwmPin pinB,
                          PwmPin pinC);
};
