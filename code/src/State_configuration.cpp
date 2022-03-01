#include <State_configuration.hpp>

State_configuration::State_configuration(const int state)
{
    current = state;
}

State_configuration::~State_configuration()
{
}

State_configuration& State_configuration::onEntry(const stateCallback callback){
    entryCallback = callback;
    return *this;    
}

State_configuration& State_configuration::onExit(const stateCallback callback){
    entryCallback = callback;
    return *this;    
}

State_configuration& State_configuration::onTrigger(const int* transitionTable ){
    transition_table = transitionTable;
    return *this;
}
