
#include <Timer3Trigger.hpp>

Timer3Trigger::Timer3Trigger()
    : TimerTrigger(&TCCR3A,
                   &TCCR3B,
                   &TCCR3C,
                   &OCR3A,
                   &OCR3B,
                   &OCR3C,
                   &TIMSK3,
                   TIMER3_OVF_INTERRUPT_ID,
                   TIMER3_COMPA_INTERRUPT_ID,
                   TIMER3_COMPB_INTERRUPT_ID,
                   TIMER3_COMPC_INTERRUPT_ID,
                   TimerPwmConfiguration(&TCCR3A,
                                         PwmPin(24, &OCR3A, COM3A0, COM3A1),
                                         PwmPin(25, &OCR3B, COM3B0, COM3B1),
                                         PwmPin(26, &OCR3C, COM3C0, COM3C1)))
{
}