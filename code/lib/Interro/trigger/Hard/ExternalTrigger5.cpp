
#include <ExternalTrigger5.hpp>

ExternalTrigger5::ExternalTrigger5()
    : ExternalTrigger(&EICRB, INT5, ISC50, ISC51, INT5_INTERRUPT_ID)
{
}