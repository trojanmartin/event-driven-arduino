#include <Interro.hpp>

#if INT1_INTERRUPT
ISR(INT1_vect)
{
   interro.handleInterrupt(INT1_INTERRUPT_ID);
}
#endif

#if INT2_INTERRUPT
ISR(INT2_vect)
{
   interro.handleInterrupt(INT2_INTERRUPT_ID);
}
#endif

#if INT3_INTERRUPT
ISR(INT3_vect)
{
   interro.handleInterrupt(INT3_INTERRUPT_ID);
}
#endif

#if INT4_INTERRUPT
ISR(INT4_vect)
{
   interro.handleInterrupt(INT4_INTERRUPT_ID);
}
#endif

/* Timer1 */

#if Timer1_OVF_INTERRUPT
ISR(TIMER1_OVF_vect)
{
   interro.handleInterrupt(Timer1_OVF_INTERRUPT_ID);
}
#endif

#if Timer1_COMPA_INTERRUPT
ISR(TIMER1_COMPA_vect)
{
   interro.handleInterrupt(Timer1_COMPA_INTERRUPT_ID);
}
#endif

#if Timer1_COMPB_INTERRUPT
ISR(TIMER1_COMPB_vect)
{
   interro.handleInterrupt(Timer1_COMPB_INTERRUPT_ID);
}
#endif

#if Timer1_COMPC_INTERRUPT
ISR(TIMER1_COMPC_vect)
{
   interro.handleInterrupt(Timer1_COMPC_INTERRUPT_ID);
}
#endif