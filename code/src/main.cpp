#include <Interro.hpp>

uint8_t ledOnePin = 35;
uint8_t ledTwoPin = 43;

enum States
{
    LedOneOn,
    LedOneOff,

    LedTwoOn,
    LedTwoOff,
};

enum Events
{
    IntervalOneElapsed,
    IntervalTwoElapsed,
};

Timer1Trigger timerTrigger;

StateMachine blinkingMachineTwo(States::LedTwoOff);
StateMachine blinkingMachineOne(States::LedOneOff);

// machine one states
static const int8_t ledOneOnStateTable[]{
    Events::IntervalOneElapsed, States::LedOneOff,
    -1};

static const int8_t ledOneOffStateTable[]{
    Events::IntervalOneElapsed, States::LedOneOn,
    -1};

// machine two states
static const int8_t ledTwoOnStateTable[]{
    Events::IntervalTwoElapsed, States::LedTwoOff,
    -1};

static const int8_t ledTwoOffStateTable[]{
    Events::IntervalTwoElapsed, States::LedTwoOn,
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
    Serial.begin(9600);
    pinMode(ledOnePin, OUTPUT);
    pinMode(ledTwoPin, OUTPUT);

    // set-up machine for led 1
    blinkingMachineOne.configure(States::LedOneOn)
        .onEvent(ledOneOnStateTable)
        .onEntry([](int8_t event)
                 { TurnOnLed(ledOnePin); });

    blinkingMachineOne.configure(States::LedOneOff)
        .onEvent(ledOneOffStateTable)
        .onEntry([](int8_t event)
                 { TurnOffLed(ledOnePin); });

    // set-up machine for led 2
    blinkingMachineTwo.configure(States::LedTwoOn)
        .onEvent(ledTwoOnStateTable)
        .onEntry([](int8_t event)
                 { TurnOnLed(ledTwoPin); });

    blinkingMachineTwo.configure(States::LedTwoOff)
        .onEvent(ledTwoOffStateTable)
        .onEntry([](int8_t event)
                 { TurnOffLed(ledTwoPin); });

    // set-up triggers
    timerTrigger.configure(TimerMode::CTC)
        .useInterval(1000, Events::IntervalOneElapsed);
}

void loop()
{
    interro.run();
}