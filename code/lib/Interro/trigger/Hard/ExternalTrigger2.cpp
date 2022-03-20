
#include <ExternalTrigger2.hpp>

ExternalTrigger2::ExternalTrigger2()
    : ExternalTrigger(&EICRA, INT2, ISC20, ISC21, INT2_INTERRUPT_ID)
{
}