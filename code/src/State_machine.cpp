//
// Created by marti on 2/28/2022.
//

#include "State_machine.h"

State_machine::State_machine() {
    
}

void State_machine::trigger(int trigger) {
    current->trigger(trigger);
}

State_configuration* State_machine::Configure(int state) {
    return new State_configuration();
}