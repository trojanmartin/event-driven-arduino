#include <State_machine.h>
#include <Trigger.hpp>
#include <Arduino.h>
#include <dictionary.hpp>

#define END -1

enum State { Idle, On, Off };
enum Triggers { Timer1, ButtonClicked };

state_machine machine(Idle);
trigger buttonTrigger(ButtonClicked);

void callback(int a);

const int idle_state_table[] PROGMEM {
   ButtonClicked, On,
   END
};

const int off_table[] PROGMEM {
   Timer1, On,
   ButtonClicked, Idle,
   END
};

const int on_state_table[] PROGMEM {
   Timer1, Off,
   ButtonClicked, Idle,
   END
};

void setup() {   
   machine.configure(Idle)
          .onEntry(&callback)
          .onExit(&callback)
          .onTrigger(idle_state_table);

   machine.configure(On)
          .onEntry(&callback)
          .onExit(&callback)
          .onTrigger(on_state_table);

   machine.configure(Off)
          .onEntry(&callback)
          .onExit(&callback)
          .onTrigger(off_table);   
}

void loop() {
// write your code here
}