
#include <ExternalTrigger0.hpp>

ExternalTrigger0::ExternalTrigger0()
    : ExternalTrigger(&EICRA, INT0, ISC00, ISC01, INT0_INTERRUPT_ID)
{
}