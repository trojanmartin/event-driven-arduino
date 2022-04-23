#pragma once

enum Arduino2560Pin
{
    DigitalPin0,
    DigitalPin1,
    DigitalPin2,
    DigitalPin3,
    DigitalPin4,
    DigitalPin5,
    DigitalPin6,
    DigitalPin7,
    DigitalPin8,
    DigitalPin9,
    DigitalPin10,
    DigitalPin11,
    DigitalPin12,
    DigitalPin13,
};

#define timerPwmOutputToArduinoPin(timer, output) timer == 1 ? (output == 0 ? 11 : (output == 1 ? 12 : 13)) : timer == 2 ? (output == 0 ? 10 : (output == 1 ? 9 : UNDEFINED)) \
                                                                                                          : timer == 3   ? (output == 0 ? 5 : (output == 1 ? 2 : 3))          \
                                                                                                          : timer == 4   ? (output == 0 ? 6 : (output == 1 ? 7 : 8))          \
                                                                                                          : timer == 5   ? (output == 0 ? 46 : (output == 1 ? 45 : 44))       \
                                                                                                                         : UNDEFINED