
#include <ExternalTrigger6.hpp>

ExternalTrigger6::ExternalTrigger6()
    : ExternalTrigger(&EICRB, INT6, ISC60, ISC61, INT6_INTERRUPT_ID)
{
}