
#include <Timer5Trigger.hpp>

Timer5Trigger::Timer5Trigger()
    : TimerTrigger(&TCCR5A,
                   &TCCR5B,
                   &TCCR5C,
                   &OCR5A,
                   &OCR5B,
                   &OCR5C,
                   &TIMSK5,
                   TIMER5_OVF_INTERRUPT_ID,
                   TIMER5_COMPA_INTERRUPT_ID,
                   TIMER5_COMPB_INTERRUPT_ID,
                   TIMER5_COMPC_INTERRUPT_ID,
                   TimerPwmConfiguration(5,
                                         &TCCR5A,
                                         PwmPin(&OCR5A, COM5A0, COM5A1),
                                         PwmPin(&OCR5B, COM5B0, COM5B1),
                                         PwmPin(&OCR5C, COM5C0, COM5C1)))
{
}