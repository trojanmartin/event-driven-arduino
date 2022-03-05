#pragma once

template <typename T> 
struct entry { 
  int key; 
  T *value; 
}; 


template <typename T>
class dictionary
{
private:
    int capacity = 0;
    int current_size = 0;
    entry<T>* store;    

public:
    T& get(int key);
    void add(int key, T& value);
    dictionary(int initial_capacity);
    ~dictionary();
};

template <typename T>
dictionary<T>::dictionary(int initial_capacity) {
    capacity = initial_capacity;
    store = new entry<T>[initial_capacity];
}

template <typename T>
void dictionary<T>::add(int key, T& value) {
    if(current_size == capacity) {
       //TODO: Allocate new array.
       return;
    }

    entry<T>& new_one = *new entry<T>();
    new_one.key = key;
    new_one.value = &value;
    store[current_size] = new_one;    
    current_size++;
}

template <typename T>
T& dictionary<T>::get(int key){
    for(int i = 0; i < current_size; i++){
        if((store + i)->key == key){
            return *((store + i)->value);
        }
    }

    return *((store + 0)->value);
}

template <typename T>
dictionary<T>::~dictionary()
{
    for(int i = 0; i < current_size; i++){
        delete (store + i)->value;
        delete (store + i);
    }
}
