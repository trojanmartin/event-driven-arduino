#pragma once

template <typename T> 
struct entry { 
  int8_t key; 
  T *value; 
}; 


template <typename T>
class dictionary
{
private:
    int8_t capacity = 0;
    int8_t current_size = 0;
    entry<T>* store;    

public:
    T& get(int8_t key);
    void add(int8_t key, T& value);
    dictionary(int8_t initial_capacity);
    ~dictionary();
};

template <typename T>
dictionary<T>::dictionary(int8_t initial_capacity) {
    capacity = initial_capacity;
    store = new entry<T>[initial_capacity];
}

template <typename T>
void dictionary<T>::add(int8_t key, T& value) {
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
T& dictionary<T>::get(int8_t key){
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
