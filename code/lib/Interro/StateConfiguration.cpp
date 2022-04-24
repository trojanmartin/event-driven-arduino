#include <StateConfiguration.hpp>

StateConfiguration::StateConfiguration(const uint8_t state)
{
    entry_callback = 0;
    exit_callback = 0;
    transition_table = 0;
    currentState = state;
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
