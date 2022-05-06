#pragma once

#include <Arduino.h>
#include <HardTrigger.hpp>

enum TimerMode
{
    Normal,
    CTC,
    PWM
};

enum Prescalers
{
    Prescaler1,
    Prescaler8,
    Prescaler64,
    Prescaler256,
    Prescaler1024
};

class TimerTrigger : public HardTrigger
{
private:
    const uint16_t prescalers[5]{1, 8, 64, 256, 1024};
    const uint16_t maxTick = 65535;
    int8_t prescalerIndex = UNDEFINED;
    TimerMode timerMode;

    volatile uint8_t *TCCRnA;
    volatile uint8_t *TCCRnB;
    volatile uint8_t *TCCRnC;

    double ocrnaFrequency;
    volatile uint16_t *OCRnA;

    double ocrnbFrequency;
    volatile uint16_t *OCRnB;

    double ocrncFrequency;
    volatile uint16_t *OCRnC;

    uint8_t WGMn3 = 4;
    uint8_t WGMn2 = 3;
    uint8_t WGMn1 = 1;
    uint8_t WGMn0 = 0;
    uint8_t CSn2 = 2;
    uint8_t CSn1 = 1;
    uint8_t CSn0 = 0;

    volatile uint8_t *TIMSKn;
    uint8_t ICIEn = 5;
    uint8_t OCIEnC = 3;
    uint8_t OCIEnB = 2;
    uint8_t OCIEnA = 1;
    uint8_t TOIEn = 0;

    uint8_t onEverflowInterrupt;
    int8_t onOverflowEvent = UNDEFINED;

    uint8_t onCompareMatchAInterrupt;
    int8_t onCompareMatchAEvent = UNDEFINED;

    uint8_t onCompareMatchBInterrupt;
    int8_t onCompareMatchBEvent = UNDEFINED;

    uint8_t onCompareMatchCInterrupt;
    int8_t onCompareMatchCEvent = UNDEFINED;

    TimerPwmConfiguration pwmConfiguration;

    int8_t handleInterrupt(interrupt interrupt);
    void calculateCompareRegisterValue(double frequency, uint8_t *prescalerIndex, uint16_t *compareValue);
    void setPrescaler(uint8_t index);
    uint8_t findIntersection(uint8_t result[], uint8_t first[], size_t firstCount, uint8_t second[], size_t secondCount);
    void setCompareMatchRegister(volatile uint16_t *occrnx, uint16_t compareValue, volatile uint8_t *timskn, uint8_t ocienx);
    void getPossiblePrescalers(double frequency, uint8_t prescalerindexes[], uint16_t compareValues[], uint8_t *count);
    double getFrequency(uint8_t prescalerIndex, uint16_t comapareValue);
    TimerTrigger &setTimer(const uint32_t miliss, const uint8_t event, bool mainInterval);

public:
    TimerTrigger &configure(TimerMode mode);
    TimerTrigger &setPrescalerValue(Prescalers value);
    TimerTrigger &useInterval(const uint32_t millis, const uint8_t event);
    TimerTrigger &onTime(const uint32_t millis, const uint8_t event);
    TimerTrigger &onOverflow(const uint8_t event);
    TimerPwmConfiguration &setPwmMode(PwmMode mode);
    TimerPwmConfiguration &getPwmConfigurator();
    TimerTrigger(volatile uint8_t *TCCRnA,
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
                 TimerPwmConfiguration pwm);
};