
#include <Timer4Trigger.hpp>

Timer4Trigger::Timer4Trigger()
    : TimerTrigger(&TCCR4A, &TCCR4B, &TCCR4C, &OCR4A, &OCR4B, &OCR4C, &TIMSK4, TIMER4_OVF_INTERRUPT_ID, TIMER4_COMPA_INTERRUPT_ID, TIMER4_COMPB_INTERRUPT_ID, TIMER4_COMPC_INTERRUPT_ID)
{
}