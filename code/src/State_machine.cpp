//
// Created by marti on 2/28/2022.
//

#include "State_machine.h"

State_machine::State_machine(const int intialState) {
    
}


State_configuration& State_machine::configure(const int state) {
    return *new State_configuration(state);
}