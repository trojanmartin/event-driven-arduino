#include <Interro.hpp>

enum States
{
    LedOn,
    LedOff,
    Idle
};

enum Events
{
    ButtonClicked,
    TimeElapsed,
};

Timer1Trigger timerTrigger;
ButtonTrigger buttonTrigger;

StateMachine blinkingMachine(States::Idle);

static const int8_t idleStateTable[]{
    Events::ButtonClicked, States::LedOn,
    -1};

static const int8_t ledOnStateTable[]{
    Events::ButtonClicked, States::Idle,
    Events::TimeElapsed, States::LedOff,
    -1};

static const int8_t ledOffStateTable[]{
    Events::ButtonClicked, States::Idle,
    Events::TimeElapsed, States::LedOn,
    -1};

void TurnOnLed()
{
}

void TurnOffLed()
{
}

void setup()
{
    blinkingMachine.configure(States::Idle)
        .onEvent(idleStateTable);

    blinkingMachine.configure(States::LedOn)
        .onEvent(ledOnStateTable)
        .onEntry([](int8_t state)
                 { TurnOnLed(); });

    blinkingMachine.configure(States::LedOff)
        .onEvent(ledOffStateTable)
        .onEntry([](int8_t state)
                 { TurnOffLed(); });

    timerTrigger.configure(TimerMode::CTC)
        .onTimeElapsed(1000, Events::TimeElapsed);

    buttonTrigger.configure(5)
        .onClick(Events::ButtonClicked);
}

void loop()
{
    interro.run();
}