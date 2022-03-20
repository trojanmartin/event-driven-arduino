
#include <ExternalTrigger7.hpp>

ExternalTrigger7::ExternalTrigger7()
    : ExternalTrigger(&EICRB, INT7, ISC70, ISC71, INT7_INTERRUPT_ID)
{
}