#include <Interro.hpp>

enum State
{
    Idle,
    Quarter,
    Half,
    ThreQuarter
};
enum Events
{
    ButtonClicked,
    TimeElapsed,
};

ButtonTrigger buttonTrigger;
Timer1Trigger timer1;
Timer3Trigger timer3;
StateMachine machine(Idle);

static const int8_t idle_state_table[]{
    ButtonClicked, Quarter,
    -1};

static const int8_t quarter_state_table[]{
    ButtonClicked, Idle,
    TimeElapsed, Half,
    -1};

static const int8_t half_table[]{
    ButtonClicked, Idle,
    TimeElapsed, ThreQuarter,
    -1};

static const int8_t threQuarter_table[]{
    ButtonClicked, Idle,
    TimeElapsed, Quarter,
    -1};

void setLedLuminance(double value)
{
    auto pwmConfigurator = timer1.getPwmConfigurator();
    pwmConfigurator.setUpOutput(TimerPwmOutput::C, value);
}

void setup()
{
    Serial.begin(9600);
    machine.configure(Idle)
        .onEvent(idle_state_table)
        .onEntry([](int8_t event)
                 { setLedLuminance(0); });

    machine.configure(Quarter)
        .onEvent(quarter_state_table)
        .onEntry([](int8_t event)
                 { setLedLuminance(0.25); });

    machine.configure(Half)
        .onEvent(half_table)
        .onEntry([](int8_t event)
                 { setLedLuminance(0.75); });

    machine.configure(ThreQuarter)
        .onEvent(threQuarter_table)
        .onEntry([](int8_t event)
                 { setLedLuminance(1); });

    timer3.configure(TimerMode::CTC)
        .onTimeElapsed(1000, TimeElapsed);

    buttonTrigger.configure(5)
        .onClick(ButtonClicked);

    auto pwmConfigurator = timer1.configure(TimerMode::PWM)
                               .setPrescalerValue(Prescalers::Prescaler64)
                               .setPwmMode(PwmMode::FastPwm8Bit);

    pwmConfigurator.setUpOutput(TimerPwmOutput::C, 0);
}

void loop()
{
    interro.run();
}