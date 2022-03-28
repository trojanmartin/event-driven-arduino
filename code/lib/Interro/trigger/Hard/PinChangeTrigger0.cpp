
#include <PinChangeTrigger0.hpp>

PinChangeTrigger0::PinChangeTrigger0()
    : PinChangeTrigger(&PCMSK0, PCIE0, 0, 7, PICINT0_INTERRUPT_ID)
{
}