
#include <ExternalTrigger3.hpp>

ExternalTrigger3::ExternalTrigger3()
    : ExternalTrigger(&EICRA, INT3, ISC30, ISC31, INT3_INTERRUPT_ID)
{
}