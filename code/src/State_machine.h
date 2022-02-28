//
// Created by marti on 2/22/2022.
//

#ifndef UNTITLED_STATE_MACHINE_H
#define UNTITLED_STATE_MACHINE_H

struct State_configuration;

struct Transition {
    State_configuration *next;    
};

struct State_configuration {
    Transition transitions[10];
    
    State_configuration& onEntry(){
        return *this;    
    }

    State_configuration& onTrigger(int trigger, int next){
        return *this;    
    }

    void trigger(int trigger){
        
    }
};


struct Trigger
{
    int trigger;

};


class State_machine {
private:
    void trigger(int trigger);
    State_configuration *current;

public:
    State_configuration * Configure(int state);
    State_machine();
};


#endif //UNTITLED_STATE_MACHINE_H
