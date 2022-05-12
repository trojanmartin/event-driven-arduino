#include <Interro.hpp>

uint8_t ledPin = 35;
uint8_t buttonPin = 43;

enum States
{
    LedOn,
    LedOff
};

enum Events
{
    ButtonClicked,
};

ButtonTrigger buttonTrigger;

StateMachine blinkingMachineOne(States::LedOff);

static const int8_t ledOnStateTable[]{
    Events::ButtonClicked, States::LedOff,
    -1};

static const int8_t ledOffStateTable[]{
    Events::ButtonClicked, States::LedOn,
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
    buttonTrigger.configure(buttonPin)
        .debounce(400)
        .onClick(Events::ButtonClicked);
}

void loop()
{
    interro.run();
}