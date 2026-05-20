#include "LinkedList.hpp"
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
        if(stack.empty()) return;
        stack.removeAt(0);
    }
    T* top() {
        return stack.head ? &stack.head->data : nullptr;
    }
    int size() {
        return stack.size();
    }
};