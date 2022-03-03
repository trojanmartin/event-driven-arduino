
class trigger
{
private:
     int id;
     void addListener(void (*trigger_callback)(int));
public:
    trigger(int trigger);
    ~trigger();
};

trigger::trigger(int trigger)
{
}

trigger::~trigger()
{
}

