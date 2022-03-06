#include <Interro.hpp>

#define END -1

enum State { Idle, On, Off };
enum Events { Timer1, ButtonClicked };

ButtonTrigger buttonTrigger(2);
StateMachine machine(Idle);




void callback(int8_t a)
{
   Serial.print("\n entering state");
   Serial.print(a);
}

void callbackexit(int8_t a)
{
    Serial.print("\n exiting state");
    Serial.print(a);
}

state_callback cb = &callback;

static const int8_t idle_state_table[] {
   ButtonClicked, On,
   END
};

static const int8_t on_state_table[] {
   Timer1, Off,
   ButtonClicked, Off,
   END
};

static const int8_t off_table[] {
   Timer1, On,
   ButtonClicked, Idle,
   END
};

void setup() {   
/*

   timer_1_trigger.configure()
                  .onTimeElapsed(100)
                  .fireEvent(Timer1)

                  .configure()
                  .onTimeElapsed(500)
                  .fireEvent(Timer2);
   */
   Serial.begin(9600);

   buttonTrigger.configure()
                .onClick(ButtonClicked);                 

   auto a = machine.configure(Idle)
          .onEntry(&callback)
          .onExit(&callbackexit)
          .onTrigger(idle_state_table);  

   machine.configure(On)
          .onEntry(&callback)
          .onExit(&callbackexit)
          .onTrigger(on_state_table);

   machine.configure(Off)
          .onEntry(&callback)
          .onExit(&callbackexit)
          .onTrigger(off_table);   

         
}

void loop() {
   interro.run();
}
