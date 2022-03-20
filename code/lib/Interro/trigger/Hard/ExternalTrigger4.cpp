
#include <ExternalTrigger4.hpp>

ExternalTrigger4::ExternalTrigger4()
    : ExternalTrigger(&EICRB, INT4, ISC40, ISC41, INT4_INTERRUPT_ID)
{
}