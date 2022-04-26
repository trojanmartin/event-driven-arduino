#include <Interro.hpp>

enum State
{
    Idle,
    Quarter,
    Half,
    ThreQuarter
};
enum SecondMachineStates
{
    SecondIdle = 4,
    Active
};

enum Events
{
    ButtonClicked,
    TimeElapsed,
};
enum SecondMachineEvents
{
    PinChanged = 3
};

ButtonTrigger buttonTrigger;
Timer1Trigger timer1;
Timer3Trigger timer3;
PinChangeTrigger0 pinChange0Trigger;

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

StateMachine secondMachine(SecondMachineStates::SecondIdle);
static const int8_t second_idle_state_table[]{
    PinChanged, Active,
    -1};

static const int8_t second_active_state_table[]{
    PinChanged, SecondIdle,
    -1};

void setLedLuminance(double value)
{
    auto pwmConfigurator = timer1.getPwmConfigurator();
    pwmConfigurator.setUpOutput(TimerPwmOutput::C, value);
}

uint8_t pinAa = 52;

void configureBlinkingMachine()
{
    machine.configure(Idle)
        .onEvent(idle_state_table)
        .onEntry([](int8_t event)
                 { setLedLuminance(0);
                   digitalWrite(pinAa, !digitalRead(pinAa)); });

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

void configureSecondMachine()
{
    secondMachine.configure(SecondIdle)
        .onEvent(second_idle_state_table)
        .onEntry([](int8_t event)
                 { Serial.println("Second machine idle entry"); });

    secondMachine.configure(Active)
        .onEvent(second_active_state_table)
        .onEntry([](int8_t event)
                 { Serial.println("Second machine Active entry"); });

    pinChange0Trigger.configure()
        .enableDigitalPin(pinAa)
        .onOccurrence(PinChanged);
}

void setup()
{
    Serial.begin(9600);

    configureBlinkingMachine();
    configureSecondMachine();
}

void loop()
{
    interro.run();
}