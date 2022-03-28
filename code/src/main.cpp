#include <Interro.hpp>

#define END -1

enum State
{
    Idle,
    On,
    Off,
};
enum Events
{
    Timer1,
    ButtonClicked,
};
uint8_t ledPin = 13;

// ButtonTrigger buttonTrigger;
ExternalTrigger4 external4Trigger;
PinChangeTrigger0 pinChangeTrigger;
Timer1Trigger timer1;
StateMachine machine(Idle);

void callback(int8_t a);
void callbackexit(int8_t a);

void onOffEntryCallback(int8_t a);
void onOnEntryCallback(int8_t a);

static const int8_t idle_state_table[]{
    ButtonClicked, On,
    END};

static const int8_t on_state_table[]{
    Timer1, Off,
    ButtonClicked, Idle,
    END};

static const int8_t off_table[]{
    Timer1, On,
    ButtonClicked, Idle,
    END};

void setup()
{
    Serial.begin(9600);

    pinMode(ledPin, OUTPUT);

    timer1.configure(TimerMode::CTC)
        .onTimeElapsed(500, Timer1);

    /*  external4Trigger.configure(ExternalTriggerMode::Change)
          .onOccurrence(ButtonClicked);
  */

    pinChangeTrigger.configure()
        .onOccurrence(ButtonClicked)
        .enablePin(4);

    machine.configure(Idle)
        .onEntry(&callback)
        .onExit(&callbackexit)
        .onEvent(idle_state_table);

    machine.configure(On)
        .onEntry(&onOnEntryCallback)
        .onExit(&callbackexit)
        .onEvent(on_state_table);

    machine.configure(Off)
        .onEntry(&onOffEntryCallback)
        .onExit(&callbackexit)
        .onEvent(off_table);
}

void loop()
{
    interro.run();
}

void onOffEntryCallback(int8_t a)
{
    digitalWrite(ledPin, 0);
}
void onOnEntryCallback(int8_t a)
{
    digitalWrite(ledPin, 1);
}

void callback(int8_t a)
{
    // Serial.print("\n");
    //  Serial.print(a);
    // Serial.print(millis());
}

void callbackexit(int8_t a)
{
    // Serial.print("\n entering state ");
    // Serial.print(a);
    // Serial.print("\n");
    // Serial.print(millis());
}
