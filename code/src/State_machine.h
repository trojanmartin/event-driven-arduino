//
// Created by marti on 2/22/2022.
//

#include <dictionary.hpp>
#include <state_configuration.hpp>


#ifndef UNTITLED_STATE_MACHINE_H
#define UNTITLED_STATE_MACHINE_H


class state_machine {
private:
    int initial;
    void trigger(int trigger);
    dictionary<state_configuration>* dic;
    state_configuration *current;

public:
    state_configuration& configure(int state);
    state_machine(const int initial_state);
    ~state_machine();
};


#endif //UNTITLED_STATE_MACHINE_H
