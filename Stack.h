#pragma once
#include <iostream>
#include <cstring>
template <typename T>


class Stack{
private:
    T* _array;
    size_t _size;
    size_t _top;
    bool _isEmpty = true;
    void Expand() {
        _size=_size * 2;
        T* temp_arr = new T[_size];
        std::memcpy(temp_arr, _array, _size * sizeof(T));
        delete[] _array;
        _array = temp_arr;
    }

public:                                                                             
    Stack(size_t size = 10){
        _array = new T[size];
        _size = size;
        _top = 0;
    }
    bool IsEmpty() const {
        return _isEmpty;
    }
    bool IsFull() const {
        return _size - 1 == _top && !_isEmpty;
    }
    
    void Push(T elem){
        if(IsFull())
            Expand();
        if (IsEmpty())
            _isEmpty = false;
        else
            _top++;
        _array[_top] = elem;
    }
    size_t GetLength(){
        return _size;
    }
    T Pop(){
        if(IsEmpty())
            throw "stack is empty";
        if(_top == 0){
            _isEmpty = true;
            return _array[_top];
        }
        return _array[_top--];
    }

    T Check()const{
        return _array[_top];
    }

    ~Stack(){
        delete[] _array;
    }
    friend std::ostream& operator<<(std::ostream& os, const Stack& s){
        if(s.IsEmpty())
            os << "stack is empty";
        else
            for(size_t i = 0; i <= s._top; i++)
                os << s._array[i] << " ";
            
        
        return os;
    }

};