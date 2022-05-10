#include <Interro.hpp>

uint8_t ledPin = 35;

enum States
{
    LedOn,
    LedOff
};

enum Events
{
    IntervalOneElapsed,
};

Timer1Trigger timerTrigger;

StateMachine blinkingMachineOne(States::LedOff);

static const int8_t ledOnStateTable[]{
    Events::IntervalOneElapsed, States::LedOff,
    -1};

static const int8_t ledOffStateTable[]{
    Events::IntervalOneElapsed, States::LedOn,
    -1};

void TurnOnLed(uint8_t pin)
{
    digitalWrite(pin, HIGH);
}

void TurnOffLed(uint8_t pin)
{
    digitalWrite(pin, LOW);
}

void setup()
{
    pinMode(ledPin, OUTPUT);

    blinkingMachineOne.configure(States::LedOn)
        .onEvent(ledOnStateTable)
        .onEntry([](int8_t event)
                 { TurnOnLed(ledPin); });

    blinkingMachineOne.configure(States::LedOff)
        .onEvent(ledOffStateTable)
        .onEntry([](int8_t event)
                 { TurnOffLed(ledPin); });

    // set-up triggers
    timerTrigger.configure(TimerMode::CTC)
        .useInterval(1000, Events::IntervalOneElapsed);
}

void loop()
{
    interro.run();
}