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
