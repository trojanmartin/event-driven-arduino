//
// Created by marti on 2/22/2022.
//

#include <State_configuration.hpp>

#ifndef UNTITLED_STATE_MACHINE_H
#define UNTITLED_STATE_MACHINE_H


class State_machine {
private:
    void trigger(int trigger);
    State_configuration *current;

public:
    State_configuration& configure(int state);
    State_machine(const int initialState);
};


#endif //UNTITLED_STATE_MACHINE_H
