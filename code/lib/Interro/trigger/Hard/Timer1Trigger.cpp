
#include <Timer1Trigger.hpp>

Timer1Trigger::Timer1Trigger()
    : TimerTrigger(&TCCR1A,
                   &TCCR1B,
                   &TCCR1C,
                   &OCR1A,
                   &OCR1B,
                   &OCR1C,
                   &TIMSK1,
                   TIMER1_OVF_INTERRUPT_ID,
                   TIMER1_COMPA_INTERRUPT_ID,
                   TIMER1_COMPB_INTERRUPT_ID,
                   TIMER1_COMPC_INTERRUPT_ID,
                   TimerPwmConfiguration(&TCCR1A,
                                         PwmPin(24, &OCR1A, COM1A0, COM1A1),
                                         PwmPin(25, &OCR1B, COM1B0, COM1B1),
                                         PwmPin(26, &OCR1C, COM1C0, COM1C1)))
{
}