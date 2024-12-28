#pragma once
#include <iostream>


template<typename T>
class Stack {
private:
    T* _pMem;
    size_t _size;
    int _top; 
    bool _isEmpty = true; 
    void Expand() {
        _size *= 2;
        T* arr = new T[_size];
        for (size_t i = 0; i < _size / 2; i++) arr[i] = _pMem[i];
        delete [] _pMem;
        _pMem = arr;

    }
    void Reduce() {
        if (_size <= 100) return; 
        _size /= 2;
        T* arr = new T[_size]; 
        for (size_t i = 0; i < _top + 1; i++) arr[i] = _pMem[i];
        delete [] _pMem;
        _pMem = arr;
    }

public:
    Stack(size_t size) {
        _pMem = new T[size];
        _size = size;
        _top = -1;
    }
    ~Stack() {
        delete [] _pMem; 
    }
    void Push(const T& elem) {
        if (_isEmpty) _isEmpty = false;
        if(isFull()) Expand();
        _pMem[++_top] = elem;         
    }

    T Pop() {
        if(_isEmpty) throw "Stack is empty";
        if ((_top + 1) < _size / 4) Reduce();
        if(_top == 0) _isEmpty = true;
        return _pMem[_top--];
    }
    T Top() const {
        if (_isEmpty) throw "Stack is empty";
        return _pMem[_top];
    }
    int GetIndexTop() { return _top; }

    bool isFull() const {
        return (_top + 1 == _size);
    }
    
    bool isEmpty() const { return _top == -1; }

    friend std :: ostream & operator<<(std :: ostream& os, const Stack& stack) {
        os << "( ";
        for (size_t i = 0; i < stack._top + 1; i++){
            if (i != stack._top) os << stack._pMem[i] << ", "; 
            else os << stack._pMem[i] << " )";
        }
        os << std :: endl;
        return os;
    }

    size_t GetSize() const { return _size; }
};
