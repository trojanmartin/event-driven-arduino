
class Trigger
{
private:
     int trigger;
     void addListener(void (*triggerCallback)(int));
public:
    Trigger(int trigger);
    ~Trigger();
};

Trigger::Trigger(int trigger)
{
}

Trigger::~Trigger()
{
}

