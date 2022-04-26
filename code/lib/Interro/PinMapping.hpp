#pragma once

#if defined(__AVR_ATmega2560__)

#define timerPwmOutputToArduinoPin(timer, output) timer == 1 ? (output == 0 ? 11 : (output == 1 ? 12 : 13)) : timer == 2 ? (output == 0 ? 10 : (output == 1 ? 9 : UNDEFINED)) \
                                                                                                          : timer == 3   ? (output == 0 ? 5 : (output == 1 ? 2 : 3))          \
                                                                                                          : timer == 4   ? (output == 0 ? 6 : (output == 1 ? 7 : 8))          \
                                                                                                          : timer == 5   ? (output == 0 ? 46 : (output == 1 ? 45 : 44))       \
                                                                                                                         : UNDEFINED

#define arduinoDigitalPinToPCINT(pin) pin == 53 ? 0 : pin == 53 ? 0 \
                                                  : pin == 52   ? 1 \
                                                  : pin == 51   ? 2 \
                                                  : pin == 50   ? 3 \
                                                  : pin == 10   ? 4 \
                                                  : pin == 11   ? 5 \
                                                  : pin == 12   ? 6 \
                                                  : pin == 13   ? 7 \
                                                  : pin == 0    ? 8 \
                                                                : UNDEFINED

#define arduinoAnalogPinToPCINT(pin) pin == 8 ? 16 : pin == 9 ? 17 \
                                                 : pin == 10  ? 18 \
                                                 : pin == 11  ? 19 \
                                                 : pin == 12  ? 20 \
                                                 : pin == 13  ? 21 \
                                                 : pin == 14  ? 22 \
                                                 : pin == 15  ? 23 \
                                                              : UNDEFINED



#else
#error Only Arduino2560 is currently supported

#endif