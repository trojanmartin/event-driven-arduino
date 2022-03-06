#pragma once

#include "Arduino.h"

typedef void (*state_callback)(int8_t state);

class StateConfiguration
{
private:
    uint8_t currentState;


    friend class StateMachine;
public:
    const int8_t* transition_table;
    state_callback entry_callback;
    state_callback exit_callback;
    StateConfiguration& onEntry(const state_callback callback);
    StateConfiguration& onExit(const state_callback callback);
    StateConfiguration& onEvent(const int8_t* transition_table);
    StateConfiguration(const uint8_t state);
    ~StateConfiguration();
};