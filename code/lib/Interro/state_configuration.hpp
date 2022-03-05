#pragma once

typedef void (*state_callback)(int state);

class state_configuration
{
private:
    int current;
    const int* transition_table;
    state_callback entry_callback;
    state_callback exit_callback;
public:
    state_configuration& onEntry(const state_callback callback);
    state_configuration& onExit(const state_callback callback);
    state_configuration& onTrigger(const int* transition_table);
    state_configuration(const int state);
    ~state_configuration();
};