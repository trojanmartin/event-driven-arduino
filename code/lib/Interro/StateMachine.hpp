//
// Created by marti on 2/22/2022.
//
#pragma once

#include <Interro.hpp>

#ifndef UNTITLED_STATE_MACHINE_H
#define UNTITLED_STATE_MACHINE_H

class StateMachine
{
private:
    int8_t initial;
    StateMachine *next;
    dictionary<StateConfiguration> *dic;

    void onEvent(int8_t event);
    friend class Interro;

public:
    StateConfiguration *current;
    StateConfiguration &configure(int8_t state);
    StateMachine(const int8_t initial_state);
    ~StateMachine();
};

#endif // UNTITLED_STATE_MACHINE_H
