#include <StateConfiguration.hpp>

StateConfiguration::StateConfiguration(const uint8_t state)
{
    currentState = state;
}

StateConfiguration::~StateConfiguration()
{
}

StateConfiguration &StateConfiguration::onEntry(const state_callback callback)
{
    entry_callback = callback;
    return *this;
}

StateConfiguration &StateConfiguration::onExit(const state_callback callback)
{
    exit_callback = callback;
    return *this;
}

StateConfiguration &StateConfiguration::onEvent(const int8_t *transitionTable)
{
    transition_table = transitionTable;
    return *this;
}
