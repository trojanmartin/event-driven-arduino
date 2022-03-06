//
// Created by marti on 2/28/2022.
//

#include <StateMachine.hpp>

StateMachine::StateMachine(const int8_t initial_state) {
    initial = initial_state;
    dic = new dictionary<StateConfiguration>(10);
    interro.add(*this); 
}

void StateMachine::onEvent(int8_t event) {
   auto table = current->transition_table;
   int8_t index = 0;
   
   while (table[index] != -1)
   {
       int8_t currentEvent = table[index];        
       if(currentEvent == event)
       {    
            current->exit_callback(current->currentState);
            current = &dic->get(table[index + 1]);
            current->entry_callback(current->currentState);
            break;
       }

       index += 2;
   }   
   
}

StateConfiguration& StateMachine::configure(const int8_t state) {
    auto newOne = new StateConfiguration(state);
    
    dic->add(state, *newOne);
    if(state == initial)
    {
        current = newOne;
    }
    return *newOne;
}

StateMachine::~StateMachine(){
    delete dic;
}