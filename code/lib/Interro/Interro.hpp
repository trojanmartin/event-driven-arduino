#pragma once

#define __ASSERT_USE_STDERR

#include <Arduino.h>

typedef uint8_t interrupt;
#define UNDEFINED -1

#define INT0_INTERRUPT 1
#define INT1_INTERRUPT 1
#define INT2_INTERRUPT 1
#define INT3_INTERRUPT 1
#define INT4_INTERRUPT 1
#define INT5_INTERRUPT 1
#define INT6_INTERRUPT 1
#define INT7_INTERRUPT 1

#define PICINT0_INTERRUPT 1
#define PICINT1_INTERRUPT 1
#define PICINT2_INTERRUPT 1

#define TIMER1_OVF_INTERRUPT 1
#define TIMER1_COMPA_INTERRUPT 1
#define TIMER1_COMPB_INTERRUPT 1
#define TIMER1_COMPC_INTERRUPT 1

#define TIMER3_OVF_INTERRUPT 1
#define TIMER3_COMPA_INTERRUPT 1
#define TIMER3_COMPB_INTERRUPT 1
#define TIMER3_COMPC_INTERRUPT 1

#define TIMER4_OVF_INTERRUPT 1
#define TIMER4_COMPA_INTERRUPT 1
#define TIMER4_COMPB_INTERRUPT 1
#define TIMER4_COMPC_INTERRUPT 1

#define TIMER5_OVF_INTERRUPT 1
#define TIMER5_COMPA_INTERRUPT 1
#define TIMER5_COMPB_INTERRUPT 1
#define TIMER5_COMPC_INTERRUPT 1

/* External interrupts */

#define INT0_INTERRUPT_ID 0
#define INT1_INTERRUPT_ID 1
#define INT2_INTERRUPT_ID 2
#define INT3_INTERRUPT_ID 3
#define INT4_INTERRUPT_ID 4
#define INT5_INTERRUPT_ID 5
#define INT6_INTERRUPT_ID 6
#define INT7_INTERRUPT_ID 6

/* Pin change interrupts */

#define PICINT0_INTERRUPT_ID 7
#define PICINT1_INTERRUPT_ID 8
#define PICINT2_INTERRUPT_ID 9

/* TIMERs  */

/* TIMERs  1 */
#define TIMER1_OVF_INTERRUPT_ID 10
#define TIMER1_COMPA_INTERRUPT_ID 11
#define TIMER1_COMPB_INTERRUPT_ID 12
#define TIMER1_COMPC_INTERRUPT_ID 13

/* TIMERs  2 */
#define TIMER2_OVF_INTERRUPT_ID 14
#define TIMER2_COMPA_INTERRUPT_ID 15
#define TIMER2_COMPB_INTERRUPT_ID 16

/* TIMERs  3 */
#define TIMER3_OVF_INTERRUPT_ID 17
#define TIMER3_COMPA_INTERRUPT_ID 18
#define TIMER3_COMPB_INTERRUPT_ID 19
#define TIMER3_COMPC_INTERRUPT_ID 20

/* TIMERs  4 */
#define TIMER4_OVF_INTERRUPT_ID 21
#define TIMER4_COMPA_INTERRUPT_ID 22
#define TIMER4_COMPB_INTERRUPT_ID 23
#define TIMER4_COMPC_INTERRUPT_ID 24

/* TIMERs  5 */
#define TIMER5_OVF_INTERRUPT_ID 25
#define TIMER5_COMPA_INTERRUPT_ID 26
#define TIMER5_COMPB_INTERRUPT_ID 27
#define TIMER5_COMPC_INTERRUPT_ID 28

class Interro;
class Trigger;
class StateMachine;

extern Interro interro;

class Interro
{
private:
    Trigger *triggerRoot;
    StateMachine *machineRoot;

public:
    void handleInterrupt(interrupt interrupt);
    void onEvent(uint8_t onEvent);
    void run();
    void add(Trigger &trigger);
    void add(StateMachine &machine);
};

#include <PinMapping.hpp>
#include <StateConfiguration.hpp>
#include <StateMachine.hpp>
#include <TimerMillis.hpp>
#include <TimerPwmConfiguration.hpp>
#include <assert.h>

#include <HardTrigger.hpp>
#include <SoftTrigger.hpp>
#include <Trigger.hpp>

#include <ExternalTrigger.hpp>
#include <PinChangeTrigger.hpp>
#include <TimerTrigger.hpp>

/* Hard triggers implemented by library */
#include <Timer1Trigger.hpp>
#include <Timer3Trigger.hpp>
#include <Timer4Trigger.hpp>
#include <Timer5Trigger.hpp>

#include <ExternalTrigger0.hpp>
#include <ExternalTrigger1.hpp>
#include <ExternalTrigger2.hpp>
#include <ExternalTrigger3.hpp>
#include <ExternalTrigger4.hpp>
#include <ExternalTrigger5.hpp>
#include <ExternalTrigger6.hpp>
#include <ExternalTrigger7.hpp>

#include <PinChangeTrigger0.hpp>
#include <PinChangeTrigger1.hpp>
#include <PinChangeTrigger2.hpp>

/* Soft triggers implemented by library */
#include <ButtonTrigger.hpp>
