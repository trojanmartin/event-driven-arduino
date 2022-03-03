//
// Created by marti on 2/28/2022.
//

#include "state_machine.h"

state_machine::state_machine(const int initial_state) {
    initial = initial_state;
    dic = new dictionary<state_configuration>(10); 
}


state_configuration& state_machine::configure(const int state) {
    return *new state_configuration(state);
}

state_machine::~state_machine(){
    delete dic;
}