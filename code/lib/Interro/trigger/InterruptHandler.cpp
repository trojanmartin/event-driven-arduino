#include <Interro.hpp>

#ifdef INT4_INTERRUPT
   ISR(INT4_vect)
   {  
      interro.handleInterrupt(INT4_INTERRUPT_ID);
   }
#endif
