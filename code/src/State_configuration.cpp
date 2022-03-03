#include <state_configuration.hpp>

state_configuration::state_configuration(const int state)
{
    current = state;
}

state_configuration::~state_configuration()
{
}

state_configuration& state_configuration::onEntry(const state_callback callback){
    entry_callback = callback;
    return *this;    
}

state_configuration& state_configuration::onExit(const state_callback callback){
    entry_callback = callback;
    return *this;    
}

state_configuration& state_configuration::onTrigger(const int* transitionTable ){
    transition_table = transitionTable;
    return *this;
}
