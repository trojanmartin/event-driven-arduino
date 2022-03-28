#include <Interro.hpp>

/* External interrupts */

#if INT0_INTERRUPT
ISR(INT0_vect)
{
   interro.handleInterrupt(INT0_INTERRUPT_ID);
}
#endif

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

#if INT5_INTERRUPT
ISR(INT5_vect)
{
   interro.handleInterrupt(INT5_INTERRUPT_ID);
}
#endif

#if INT6_INTERRUPT
ISR(INT6_vect)
{
   interro.handleInterrupt(INT6_INTERRUPT_ID);
}
#endif

#if INT7_INTERRUPT
ISR(INT7_vect)
{
   interro.handleInterrupt(INT7_INTERRUPT_ID);
}
#endif

/* Pin change */

#if PICINT0_INTERRUPT
ISR(PCINT0_vect)
{
   interro.handleInterrupt(PICINT0_INTERRUPT_ID);
}
#endif

#if PICINT1_INTERRUPT
ISR(PCINT1_vect)
{
   interro.handleInterrupt(PICINT1_INTERRUPT_ID);
}
#endif

#if PICINT2_INTERRUPT
ISR(PCINT2_vect)
{
   interro.handleInterrupt(PICINT2_INTERRUPT_ID);
}
#endif

/* Timer1 */

#if TIMER1_OVF_INTERRUPT
ISR(TIMER1_OVF_vect)
{
   interro.handleInterrupt(TIMER1_OVF_INTERRUPT_ID);
}
#endif

#if TIMER1_COMPA_INTERRUPT
ISR(TIMER1_COMPA_vect)
{
   interro.handleInterrupt(TIMER1_COMPA_INTERRUPT_ID);
}
#endif

#if TIMER1_COMPB_INTERRUPT
ISR(TIMER1_COMPB_vect)
{
   interro.handleInterrupt(TIMER1_COMPB_INTERRUPT_ID);
}
#endif

#if TIMER1_COMPC_INTERRUPT
ISR(TIMER1_COMPC_vect)
{
   interro.handleInterrupt(TIMER1_COMPC_INTERRUPT_ID);
}
#endif

/* TIMER3 */
#if TIMER3_OVF_INTERRUPT
ISR(TIMER3_OVF_vect)
{
   interro.handleInterrupt(TIMER3_OVF_INTERRUPT_ID);
}
#endif

#if TIMER3_COMPA_INTERRUPT
ISR(TIMER3_COMPA_vect)
{
   interro.handleInterrupt(TIMER3_COMPA_INTERRUPT_ID);
}
#endif

#if TIMER3_COMPB_INTERRUPT
ISR(TIMER3_COMPB_vect)
{
   interro.handleInterrupt(TIMER3_COMPB_INTERRUPT_ID);
}
#endif

#if TIMER3_COMPC_INTERRUPT
ISR(TIMER3_COMPC_vect)
{
   interro.handleInterrupt(TIMER3_COMPC_INTERRUPT_ID);
}
#endif

/* TIMER4 */
#if TIMER4_OVF_INTERRUPT
ISR(TIMER4_OVF_vect)
{
   interro.handleInterrupt(TIMER4_OVF_INTERRUPT_ID);
}
#endif

#if TIMER4_COMPA_INTERRUPT
ISR(TIMER4_COMPA_vect)
{
   interro.handleInterrupt(TIMER4_COMPA_INTERRUPT_ID);
}
#endif

#if TIMER4_COMPB_INTERRUPT
ISR(TIMER4_COMPB_vect)
{
   interro.handleInterrupt(TIMER4_COMPB_INTERRUPT_ID);
}
#endif

#if TIMER4_COMPC_INTERRUPT
ISR(TIMER4_COMPC_vect)
{
   interro.handleInterrupt(TIMER4_COMPC_INTERRUPT_ID);
}
#endif

/* TIMER5 */
#if TIMER5_OVF_INTERRUPT
ISR(TIMER5_OVF_vect)
{
   interro.handleInterrupt(TIMER5_OVF_INTERRUPT_ID);
}
#endif

#if TIMER5_COMPA_INTERRUPT
ISR(TIMER5_COMPA_vect)
{
   interro.handleInterrupt(TIMER5_COMPA_INTERRUPT_ID);
}
#endif

#if TIMER5_COMPB_INTERRUPT
ISR(TIMER5_COMPB_vect)
{
   interro.handleInterrupt(TIMER5_COMPB_INTERRUPT_ID);
}
#endif

#if TIMER5_COMPC_INTERRUPT
ISR(TIMER5_COMPC_vect)
{
   interro.handleInterrupt(TIMER5_COMPC_INTERRUPT_ID);
}
#endif