//
// Created by marti on 2/28/2022.
//

#include <Interro.hpp>

StateMachine::StateMachine(const int8_t initial_state)
{
    initial = initial_state;
    interro.add(*this);
}

void StateMachine::onEvent(int8_t event)
{
    auto table = current->transition_table;
    int8_t index = 0;

    while (table[index] != -1)
    {
        int8_t currentEvent = table[index];
        if (currentEvent == event)
        {
            current->exit_callback(current->currentState);
            current = getState(table[index + 1]);
            current->entry_callback(current->currentState);
            break;
        }

        index += 2;
    }
}

StateConfiguration &StateMachine::configure(const int8_t state)
{
    auto newOne = new StateConfiguration(state);
    newOne->next = configurationRoot;
    configurationRoot = newOne;

    if (state == initial)
    {
        current = newOne;
    }
    return *newOne;
}

StateConfiguration *StateMachine::getState(uint8_t state)
{
    StateConfiguration *current;
    current = configurationRoot;
    while (current)
    {
        if (current->currentState == state)
        {
            return current;
        }
        current = current->next;
    }
    // never should get there
    assert(false);

    return 0;
}

StateMachine::~StateMachine()
{
    StateConfiguration *current;
    current = configurationRoot;
    while (current)
    {
        StateConfiguration *next;
        next = current->next;
        delete current;
        current = next;
    }
}