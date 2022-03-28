
#include <PinChangeTrigger1.hpp>

PinChangeTrigger1::PinChangeTrigger1()
    : PinChangeTrigger(&PCMSK1, PCIE1, 8, 15, PICINT1_INTERRUPT_ID)
{
}