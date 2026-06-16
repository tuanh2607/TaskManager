#ifndef STACK_HPP
#define STACK_HPP
#include "LinkedList.hpp"
#include <vector>
template<typename T>
class Stack {
private:
    LinkedList<T> stack;
public:
    bool empty() {
        return stack.size() == 0;
    }
    void push(T val) {
        stack.insertFront(val);
    }
    void pop(){
        if(stack.size() == 0) return;
        stack.removeAt(0);
    }
    T* top() {
        return stack.getHead() ? &stack.getHead()->data : nullptr;
    }
    int size() {
        return stack.size();
    }
    vector<T> toVector() {
        return stack.toVector();
    }
};
#endif