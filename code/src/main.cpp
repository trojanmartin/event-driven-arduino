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

    int output = 1;
    int timer = 0;

    auto pin = timerPwmOutputToArduinoPin(1, TimerPwmOutput::OutputB);

    Serial.print("\n asaaaaaaaaaaa");
    Serial.print(pin);

    // pinMode(ledPin, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
    TCCR2B = _BV(CS22);
    OCR2A = 254; // Duty cycle (200 + 1)/256 = 79%
    OCR2B = 100; // Duty cycle (100 + 1)/256 =  39%

    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    // OCR1A = 254;
    // OCR1B = 100;

    auto pwmConfigurator = timer1.configure(TimerMode::PWM)
                               .setPrescalerValue(256)
                               .getPwmConfigurator(PwmMode::FastPwm10Bit);

    pwmConfigurator.setUpOutput(TimerPwmOutput::OutputC, PwmPinBehavior::ClearOnCompareMatchFastPwm, 200);
    pwmConfigurator.setUpOutput(TimerPwmOutput::OutputB, PwmPinBehavior::ClearOnCompareMatchFastPwm, 255);
    pwmConfigurator.setUpOutput(TimerPwmOutput::OutputA, PwmPinBehavior::ClearOnCompareMatchFastPwm, 100);
    /*    TCCR1B |= (1 << CS11);
        TCCR1B |= (1 << CS10);
        TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
        TCCR2B = _BV(CS22);
        TCCR1B |= (1 << CS11);
        TCCR1B |= (1 << CS10);
        OCR2A = 100;
        OCR2B = 254;
        OCR2B = 254;
    */
    /*
        auto pwmConfigurator = timer1.configure(TimerMode::PWM)
                                   .getPwmConfigurator(PwmMode::FastPwm);

        pwmConfigurator.pwmPin(Arduino2560Pin::DigitalPin10)
            .setpin(PwmPinBehavior::ClearOnCompareMatch, 250);

        pwmConfigurator.setUpPin(Arduino2560Pin::DigitalPin11, PwmPinBehavior::ClearOnCompareMatch, 260);
    */
    //  TCCR1B |= (1 << CS11);
    //  TCCR1B |= (1 << CS10);
    //.setPrescalerValue(256);
    /* TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
     TCCR2B = _BV(CS22);
     OCR2A = 200; // Duty cycle (200 + 1)/256 = 79%
     OCR2B = 100; // Duty cycle (100 + 1)/256 =  39%
     */
    /*
              timer1.configure(TimerMode::CTC)
                  .onTimeElapsed(500, Timer1);

    external4Trigger.configure(ExternalTriggerMode::Change)
            .onOccurrence(ButtonClicked);


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

            */
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
