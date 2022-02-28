#include <State_machine.h>
#include <Arduino.h>

enum State {Idle, On, Off };
enum Events { TimeElapsed };

State_machine machine;

void setup() {
   auto state = machine.Configure(Idle);
   state->onEntry().onTrigger(TimeElapsed, Off);
}

void loop() {
// write your code here
}