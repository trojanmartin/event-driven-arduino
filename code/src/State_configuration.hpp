
typedef void (*stateCallback)(int state);

class State_configuration
{
private:
    int current;
    const int* transition_table;
    stateCallback entryCallback;
    stateCallback exitCallback;
public:
    State_configuration& onEntry(const stateCallback callback);
    State_configuration& onExit(const stateCallback callback);
    State_configuration& onTrigger(const int* transitionTable);
    State_configuration(const int state);
    ~State_configuration();
};