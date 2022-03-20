
#include <ExternalTrigger1.hpp>

ExternalTrigger1::ExternalTrigger1()
    : ExternalTrigger(&EICRA, INT1, ISC10, ISC11, INT1_INTERRUPT_ID)
{
}