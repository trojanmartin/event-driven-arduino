
#include <PinChangeTrigger2.hpp>

PinChangeTrigger2::PinChangeTrigger2()
    : PinChangeTrigger(&PCMSK2, PCIE2, 16, 23, PICINT2_INTERRUPT_ID)
{
}